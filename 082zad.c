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

// JMBG ima 13 cifara najveca cifra je 9 -> 9 * 13 = 117
#define X 117

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

void printOnExactDepth(Node* root, int level) {
	if (!root || level < 1)
		return;
	if (level == 1)
		printf("%d ", root->value);
	printOnExactDepth(root->left, level - 1);
	printOnExactDepth(root->right, level - 1);
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

	for (int i = 0; i < 10; i++) {
		printf("\n\nSvi leaf-ovi u stablu na nivou %d su:  ", i + 1);
		printOnExactDepth(root, i + 1);
	}

	printf("\n\n");
	return 0;
}