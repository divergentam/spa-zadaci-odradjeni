/*
65. U provom redu datoteke zad3.in je zadat broj n koji prestavlja broj elemenata stabla. U narednih n redova je
zadato n celih brojeva koji će predstavljati elemente stabla. Napisati program koji na osnovu podataka iz ulazne
datoteke formira stablo, i to tako što raspoređuje čvorove slučajnim izborom u levo ili desno podstablo. Svaki
novoubačeni element mora biti list stabla formiranog do tog trenutka. Slučajni izbor se primenjuje na izbor
svakog podstabla za smeštanje novog elementa. Nakon toga, napisati metodu koja pronalazi sva različita
pojavljivanja brojeva, kao i njihov broj pojavljivanja. Rezultat ispisati u datoteku zad3.out i to tako što će u
svakom redu biti zapisan neki element binarnog stabla, a nakon razmaka broj pojavljivanja tog elementa.
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node* left, *right;
}Node;

typedef struct list {
	int value;
	int visited;
	struct list* link;
}List;

Node* createNode(int value) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = value;
	node->left = node->right = NULL;
	return node;
}

int find(Node* root, int value) {
	return root ? (root->value == value ) || find(root->left, value) || find(root->right, value) : 0;
}

Node* addUnordered(Node* root, int value) {
	if (!root)
		root = createNode(value);
	else if (rand() % 2)
	root->left = addUnordered(root->left, value);
	else
	root->right = addUnordered(root->right, value);

	return root;
}

Node* fromFile(char* file_name) {
	FILE* f = fopen(file_name, "r");
	Node* root = NULL;
	int n;
	int val;
	fscanf(f, "%d", &n);
	while (!feof(f)) {
		fscanf(f, "%d", &val);
		root = addUnordered(root, val);
	}
	fclose(f);
	return root;
}

#define SPACE 5

void print2D(Node* root, int space) {
	if (!root)
		return;
	space += SPACE;
	print2D(root->right, space);
	printf("\n");
	for (int i = SPACE; i < space; i++) {
		printf(" ");
	}
	printf("%d", root->value);
	print2D(root->left, space);
}

List* createListNode(int val) {
	List* head = (List*)malooc(sizeof(List));
	head->value = val;
	head->visited = 1;
	head->link = NULL;
	return head;
}

List* listOfVisited(List* head, int val) {
	if (!head)
		head = createListNode(val);
	List* temp = head;
	while (temp->link) {
		temp = temp->link;
	}
	temp->link = createListNode(val);
	return head;
}

int findInList(List* head, int find) {
	while (head) {
		if (head->value == find)
			return 1;
		head = head->link;
	}
	return 0;
}



void searchTree(Node* root, List** head) {
	if (!root)
		return;
	List* temp = *head;
	if (findInList(*head, root->value)) {
		while (temp) {
			if (temp->value == root->value)
				temp->visited++;
			temp = temp->link;
		}
	}
	else {
		*head = listOfVisited(*head, root->value);
	}
	searchTree(root->left, *head);
}

void result(Node* root, char* file_name) {
	FILE* f = fopen(file_name, "w");
	

}

int main() {
	Node* root = NULL;
	root = fromFile("065zad.txt");
	print2D(root, 1);

	result(root, "065Resenje.txt");
}