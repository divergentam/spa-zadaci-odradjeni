/*
76. Udaljenost čvorova u i v računamo kao broj grana koji treba preći na putu koji
spaja u i v. Napišite funkciju int udalj(BTREE T, node u, node v)
koja vraća udaljenost čvorova u i v u stablu T
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

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

#define X 50

int size(Node* root) {
	return root ? 1 + size(root->left) + size(root->right) : 0;
}

Node* generate20(Node* root) {
	while (size(root) != 20) {
		root = addNode(root, rand() % X);
	}
	return root;
}

int isNode(Node* root, Node* node) {
	if (!root)
		return 0;
	if (node == root)
		return 1;
	return isNode(root->left, node) || isNode(root->right, node);
}

int findLevel(Node* root, Node* node, int level) {
	if (!root)
		return -1;
	if (root == node)
		return level;
	int left = findLevel(root->left, node, level + 1);
	if (left != -1)
		return left;
	int right = findLevel(root->right, node, level + 1);
}

Node* findLowestCommonNode(Node* root, Node* x, Node* y) {
	//base case 1
	if (!root)
		return NULL;
	//base case 2 if either x or y is found
	if (root == x || root == y)
		return root;
	//recursively check if x or y exists in left subtree
	Node* left = findLowestCommonNode(root->left, x, y);
	Node* right = findLowestCommonNode(root->right, x, y);

	// if x is found in one subtree and y in other 
	if (left && right)
		return root;
	// if x and y exists in left subtree
	if (left)
		return left;
	//if x and y exists in right subtree
	if (right)
		return right;
	/*
	u sustini mi trazimo prvo cvorove x i y levo i ako se oba cvora nalaze levo  oonda ce prvi put u left da se upise najnizi 
	pa posle toga ce da se update na onaj gornji blizi root-u i na kraju varcamo taj blizi
	ako se jedan nalazi levo a drugi se nalazi desno onda ce da se vrati njihov root odnosno njihov roditelj
	*/
}

int findDistance(Node* root, Node* x, Node* y) {
	Node* lca = NULL;
	if (isNode(root, x) && isNode(root, y))
		lca = findLowestCommonNode(root, x, y);
	else
		return INT_MIN;
	// nalazimo na kom su levelu x i y u odnosu na lca koji je za njih root
	return findLevel(lca, x, 0) + findLevel(lca, y, 0);
}


int main() {
	Node* root = NULL;
	root = generate20(root);

	print2D(root, 1);

	Node* node = root->left->left->left;
	printf("\nDa li postoji cvor node (%d) u stablu? odgovor: %d", node->value, isNode(root, node));
	if(isNode(root,node))
		printf("\nNode %d je na levelu %d ", node->value, findLevel(root, node, 1));

	printf("\n\n\n");
	return 0;
}