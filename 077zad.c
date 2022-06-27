/*
77. Kažemo da je čvor v binarnog stabla T k-potomak čvora u ako se v nalazi u podstablu od T kojem je u koren i
pri tome je nivo čvora v za k veći od nivoa čvora u. Tako su npr. deca nekog čvora njegovi 1-potomci, deca od
dece 2-potomci, itd. Napišite funkciju sa prototipom labeltype potomak(BTREE T, int k)
koja vraća label onog čvora binarnog stabla T koji ima najviše k-potomaka. Ako ima više takvih čvorova, vratite
labelu bilo kojeg. Funkcija treba biti nezavisna o implementaciji atp-a BTREE; ne smete koristiti pomoćne atp-ove. 
Možete definisati pomoćne funkcije i globalne promenljive.
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

#define SPACE 6

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

Node* generate20(Node* root) {
	while (size(root) != 20) {
		root = addNode(root, rand() % X);
	}
	return root;
}

int NumOfkthAncestor(Node* root, int k) {
	if (!root || k < 0)
		return 0;
	if (k == 0)
		return 1;
	return NumOfkthAncestor(root->left, k - 1) + NumOfkthAncestor(root->right, k - 1);
}

int MAX = INT_MIN;
Node* node = NULL;

int nodeWithMaxKAncestors(Node* root, int k) {
	if (!root)
		return 0;
	int temp = NumOfkthAncestor(root, k);
	if (MAX < temp) {
		MAX = temp;
		node = root;
	}
	nodeWithMaxKAncestors(root->left, k);
	nodeWithMaxKAncestors(root->right, k);
	return node->value;
}

int main() {
	Node* root = NULL;
	root = generate20(root);

	print2D(root, 1);
	printf("\n\nRoot with maximal 1-ancestor is %d\n\n", nodeWithMaxKAncestors(root, 1));

	MAX = INT_MIN;

	Node* root2 = NULL;
	root2 = addNode(root2, 10);
	root2->right = createNode(11);
	root2->right->right = createNode(12);
	root2->right->right->right = createNode(13);
	root2->right->right->left = createNode(20);
	root2->right->left = createNode(14);
	root2->right->left->right = createNode(15);
	root2->right->left->left = createNode(16);
	root2->left = createNode(17);
	root2->left->right = createNode(78);
	root2->left->left = createNode(78);	
	root2->left->right->left = createNode(78);
	root2->left->right->right = createNode(78);
	root2->left->left->right = createNode(78);
	root2->left->left->left = createNode(78);

	
	print2D(root2, 1);
	printf("\nRoot with maximal 2-ancestor is %d", nodeWithMaxKAncestors(root2, 2));


	printf("\n\n\n");
	return 0;
}