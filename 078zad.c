/*
78. Date su dve datoteke koje u svakoj liniji sadrže po jedan niz sa ne više od 80 karaktera. Napisati program koji na
standardni izlaz ispisuje sve niske prve datoteke koje nisu sadržane u drugoj datoteci. Zadatak realizovati
korišćenjem binarnog stabla pretrage
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char* sen;
	struct node* left, * right;
}Node;

Node* create(char* sen) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->sen = sen;
	node->left = node->right = NULL;
	return node;
}

Node* addNode(Node* root, char* sen) {
	if (!root)
		root = create(sen);
	else if (strcmp(root->sen, sen) > 0)
		root->left = addNode(root->left, sen);
	else if (strcmp(root->sen, sen) < 0)
		root->right = addNode(root->right, sen);
	else if (rand() % 2)
		root->left = addNode(root->left, sen);
	else 
		root->right = addNode(root->right, sen);
	return root;
}

#define MAX 80

Node* readFromFile(char* file_name) {
	FILE* f = fopen(file_name, "r");
	Node* root = NULL;
	int n;
	int count = 0;
	fscanf(f, "%d", &n);
	fgetc(f);
	for (int i = 0; i < n; i++) {
		char sen[MAX];
		fgets(sen, MAX, f);
		printf("\n%s", sen);
		root = addNode(root, sen);
		printf("root->sen: %s", root->sen);
		count = 0;
	}
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
	printf("%s  ", root->sen);
	print2D(root->left, space);
}

void print_lkd(Node* root) {
	if (root) {
		print_lkd(root->left);
		printf("%s", root->sen);
		print_lkd(root->right);
	}
}

int main() {
	Node* root = NULL;
	root = readFromFile("078zad.txt");
	print2D(root, 1);
	printf("\n\n");

	print_lkd(root);

	printf("\n\n");
	return 0;
}