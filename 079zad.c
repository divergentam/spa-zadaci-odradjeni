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

int findNode(Node* root, int value) {
	return root ? (root->value == value) || findNode(root->left, value) || findNode(root->right, value) : 0;
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

Node* checkThenAdd(Node* root, int value) {
	if (!findNode(root, value))
		return addNode(root, value);
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

int size(Node* root) {
	return root ? 1 + size(root->left) + size(root->right) : 0;
}

#define X 53

Node* generate20(Node* root) {
	while(size(root) != 20) {
		root = checkThenAdd(root, rand() % X);
	}
	return root;
}



int main() {
	Node* root = NULL;
	root = generate20(root);

	print2D(root, 1);

	return 0;
}