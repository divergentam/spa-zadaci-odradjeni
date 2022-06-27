/*
83. U binarno stablo upisuju se celobrojni podaci (int) u intervalu [1, X]. Napisati funkciju koja će u stablo dodati
novi element (ali samo ako on u stablu već ne postoji). Napisati drugu funkciju koja će za zadano stablo ispisati
sve listove tog stabla. Napisati glavni program u kojem slučajno generisati 20 brojeva u intervalu [1, X].
Koristeći prvu napisanu funkciju, tako dobijene brojeve upisati u binarno stablo. Pomoću druge napisane
funkcije ispisati sve listove dobijenog stabla.
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

#define X 50

Node* createNode(int value) {
	Node* node = (Node*)malloc(sizeof(Node));
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

int find(Node* root, int value) {
	return root ? (root->value == value) || find(root->left, value) || find(root->right, value) : 0;
}

Node* checkAndCreate(Node* root, int value) {
	if (!find(root, value))
		return addNode(root, value);
	return root;
}

int size(Node* root) {
	return root ? 1 + size(root->left) + size(root->right) : 0;
}

void printAllLeafs(Node* root) {
	if (!root)
		return;
	if (root->left == NULL && root->right == NULL)
		printf("%d  ", root->value);
	printAllLeafs(root->left);
	printAllLeafs(root->right);
}

#define SPACE 10

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

int main() {
	Node* root = NULL;

	while (size(root) != 20) {
		root = checkAndCreate(root, rand() % X);
	}
	print2D(root, 1);

	printf("\n\nSvi leaf-ovi u stablu su:  ");
	printAllLeafs(root);

	return 0;
}