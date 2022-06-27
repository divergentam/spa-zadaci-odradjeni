/* 
U datoteci 062zad.txt se nalazi niz reči (koje su zapisane u posebnim redovima datoteke) od kojih ni jedna nije
dužine veće od 30 karaktera. Ispisati na standardni izlaz samo različite reči sortirane leksikografski. Uz svaku reč
ispisati i broj pojava. Kraj unosa je marker kraja (EOF). Smatrati da je reč niska sastavljena isključivo od slova i
cifara i broj pojava svake reči nije veći od 10000.
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node {
	int appears;
	char* word;
	struct node* left;
	struct node* right;
}Node;

Node* creareNode(char* word) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->appears = 1;
	node->word = _strdup(word); // duplicate the string
	node->left = node->right = NULL;
	return node;
}

Node* addNode(Node* root, char* word) {
	int cond;
	if (!root)
		root = creareNode(word);
	//ako postoji neki node
	else if (cond = strcmp(word, root->word) == 0) { //pitamo se da li je nova rec ista kao rec koja je u root
		root->appears++;
	}
	else if (cond > 0)
		root->right = addNode(root->right, word);
	else
		root->left = addNode(root->left, word);
	return root;
}


void treeprint(Node* p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->appears, p->word);
		treeprint(p->right);
	}
}

void freeTree(Node* root) {
	if (root->left)
		freeTree(root->left);
	else if (root->right)
		freeTree(root->right);
	free(root);
}

#define MAX 31

int getWord(char w[], FILE* f) {
	char c;
	int i =0;
	while (!isalnum(c = w[0] = fgetc(f)) && c != EOF);
	if (c == EOF) {
		w[0] = '/0';
		return EOF;
	}
	while ((c == fgetc(f)) != EOF && isalnum(c) && i < MAX)
		w[++i] = c;
	w[++i] = '/0'; // kraj stringa
	if (c == EOF)
		return EOF;
	return i;
}

int main() {
	Node* root = NULL;
	char w[MAX];
	FILE* f = fopen("062zad.txt", "r");
	while (1) {
		int end = getWord(w, f); // end je duzina reci
		if (strlen(w)) // ako je vracena rec
			root = addNode(root, w);
		if (end == EOF)
			break;
	}
	treeprint(root);
	freeTree(root);

	fclose(f);
	return 0;
}