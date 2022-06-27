//void pisi_kld(Stablo koren); /* Prefiksno ispisivanje. */
//void pisi_lkd(Stablo koren); /* Infiksno ispisivanje.* /
//void pisi_ldk(Stablo koren); /* Postfiksno ispisivanje. */

/*
73. Rekonstruišite binarno stablo čiji čvorovi imaju imena A, B, . . ., J ako
je poznato da INORDER obilazak ispisuje čvorove u redosledu
GDJEAICHBF, a POSTORDER obilazak u redosledu and DJGIABHFCE.
Nakon rekonstrukcije, napišite program koji formira dato binarno
stablo i ispišite i PREORDER obilazak dobijenog stabla. Formirajte još neko stablo koje ima iste PREORDER i
POSTORDER obilaske kao ovo.
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char c;
	struct node* left, * right;
}Node;

void inOrder(Node* root) {
	if (root) {
		inOrder(root->left);
		printf("%c ", root->c);
		inOrder(root->right);
	}
}

void postOrder(Node* root) {
	if (root) {
		postOrder(root->left);
		inOrder(root->right);
		printf("%c ", root->c);
	}
}

Node* create(char c) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->c = c;
	node->left = node->right = NULL;
	return node;
}

Node* addNode(Node* root, char c) {
	if (!root)
		root = create(c);
	else if (rand() % 2)
		root->left = addNode(root->left, c);
	else 
		root->right = addNode(root->right, c);
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
	printf("%c", root->c);
	print2D(root->left, space);
}


int size(Node* root) {
	return root ? 1 + size(root->left) + size(root->right) : 0;
}

int main() {
	Node* root = NULL;
	root = addNode(root, 'A');
	root = addNode(root, 'B');
	root = addNode(root, 'C');
	root = addNode(root, 'D');
	root = addNode(root, 'E');
	root = addNode(root, 'F');
	root = addNode(root, 'G');
	root = addNode(root, 'H');
	root = addNode(root, 'I');
	root = addNode(root, 'J');

	print2D(root, 1);

	printf("\n\n");
	inOrder(root);
	printf("\n\n");

	postOrder(root);

	return 0;
}