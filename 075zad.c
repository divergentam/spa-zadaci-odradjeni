/*
75. Kažemo da je čvor p binarnog stabla zajednički predak čvorova u i v ako je p istovremeno predak čvora u i
predak čvora v. Čvor np je najbliži predak od u i v ako od svih njihovih zajedničkih
predaka upravo np ima najveću visinu. Napišite funkciju node np(BTREE T, node u, node v)
koja vraća ime najbližeg pretka čvorova u i v. U primeru desno, čvorovi a i c su zajednički 
pretci čvorova f i e - ali kako c ima veću visinu, on je najbliži predak.
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>


typedef struct node {
	int value;
	struct node* left, * right;
}Node;

Node* createNode(int value) {
	Node* node = NULL;
	node = (Node*)malloc(sizeof(Node));
	node->value = value;
	node->left = node->right = NULL;
	return node;
}

Node* addNode(Node* root, int value) {
	if (!root)
		root = createNode(value);
	else if (rand() % 2)
		root->left = addNode(root->left, value);
	else
		root->right = addNode(root->right, value);
	return root;
}

#define SPACE 5

void print2D(Node* root, int space) {
	if (!root)
		return;
	space += SPACE;
	print2D(root->right, space);
	printf("\n");
	for (int i = SPACE; i < space; i++)
		printf(" ");
	printf("%d ", root->value);
	print2D(root->left, space);
}

#define X 53

int size(Node* root) {
	return root ? 1 + size(root->left) + size(root->right) : 0;
}

Node* generate10(Node* root) {
	while (size(root) != 10) {
		root = addNode(root, rand() % X);
	}
	return root;
}

int isNode(Node* root, Node* node) {
	return root ? (root == node) || isNode(root->left, node) || isNode(root->right, node) : 0;
}

Node* findLCA(Node* root, Node* x, Node* y) {
	// base case 1
	if (!root)
		return NULL;
	// base case 2 root is either x or y we will return x or y
	if (root == x || root == y)
		return root;

	Node* left = findLCA(root->left, x, y);
	Node* right = findLCA(root->right, x, y);

	//if one of them is left and one is right we return their root
	if (left && right)
		return root;
	//if we don't have left and right but we have left then both are left
	if (left)
		return left;
	//if we don't have left and both left and right then both of them are right
	if (right)
		return right;
}

int main() {
	Node* root = NULL;
	root = generate10(root);

	print2D(root, 1);
	Node* x = root->right->right;
	Node* y = root->right->left->right;

	printf("\n\nClosest ancestor for %d and %d is %d", x->value, y->value, findLCA(root, x, y)->value);


	printf("\n\n\n");
	return 0;
}