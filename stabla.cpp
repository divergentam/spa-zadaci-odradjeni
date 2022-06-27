#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node* left, * right;
}Node;

/*
Stablo stvori(void); 
int vel(Stablo koren); 
int zbir(Stablo koren); 
void pisi_kld(Stablo koren); 
void pisi_lkd(Stablo koren); 
void pisi_ldk(Stablo koren); 
void crtaj(Stablo koren, int nivo); 
int pojav(Stablo koren, int b); 
int min_u(Stablo koren); 
int max_u(Stablo koren); 
int min_n(Stablo koren); 
int max_n(Stablo koren); 
int uredjeno(Stablo koren); 
Cvor* nadji_u(Stablo koren, int b); 
Cvor* nadji_n(Stablo koren, int b); 
Stablo dodaj_u(Stablo koren, int b); 
Stablo dodaj_n(Stablo koren, int b); 
Stablo citaj_u(int n); 
Stablo citaj_n(int n); 
Stablo brisi(Stablo koren); 
Stablo izost_u(Stablo koren, int b); 
Stablo izost_n(Stablo koren, int b); 
Stablo balans_u(Stablo koren);
Stablo balans_n(Stablo koren); 
int moze(Stablo koren); 
Stablo radi(Stablo(*f)(Stablo, int), Stablo koren; */

Node* createNode(int value) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = value;
	node->left = node->right = NULL;
	return node;
}

Node* create() {
	return NULL;
}

int size(Node* root) {
	return root ? 1 + size(root->right) + size(root->left) : 0;
}

int sum(Node* root) {
	return root ? sum(root->left) + sum(root->right) + root->value : 0;
}

void write_root_l_r(Node* root) {
	if (root) {
		printf("%d", root->value);
		write_root_l_r(root->left);
		write_root_l_r(root->right);
	}
}

void write_l_root_r(Node* root) {
	if (root) {
		write_root_l_r(root->left);
		printf("%d", root->value);
		write_root_l_r(root->right);
	}
}

void write_l_r_root(Node* root) {
	if (root) {
		write_root_l_r(root->left);
		write_root_l_r(root->right);
		printf("%d", root->value);
	}
}

// pitati za iscrtavanje stabla

// u uredjenom stablu levo su malji brojevi od korena a desno veci
//da bi nasli minimum idemo skroz levo
int minimal_o(Node* root) {
	return root->left ? minimal_o(root->left) : root->value;
}

int maximal_o(Node* root) {
	return root->right ? maximal_o(root->right) : root->value;
}

int minimal_u(Node* root) {
	int min = root->value, k;
	if (root->left) {
		k = minimal_u(root->left);
		if (k < min)
			min = k;
	}
	if (root->right) {
		k = minimal_u(root->right);
		if (k < min)
			min = k;
	}
	return min;
} 

int maximal_u(Node* root) {
	int max = root->value, k;
	if (root->left) {
		k = maximal_u(root->left);
		if (k > max)
			max = k;
	}
	if (root->right) {
		k = maximal_u(root->right);
		if (k > max)
			max = k;
	}
	return max;
}

/*
funkcionise po principu :
ako ne postoji stablo -> true
ako postoji levi pitam se da li nije uredjeno ili da li je maximalni levo veci od korena
(to se pitam jer sve vrednosti manje od korena treba da budu levo pa ako je neka veca od korena stablo nije uredjeno_
|| isto vazi za desnu stranu s tim sto desno treba da se nalaze svi brojevi veci od korena pa ako je neki manji stablo je neuredjeno
*/

int isOrdered(Node* root) {
	if (!root)
		return 1;
	if (root->left && !(isOrdered(root->left)) || maximal_u(root->left) > root->value)
		return 0;
	if (root->right && !(isOrdered(root->right)) || minimal_u(root->right) < root->value)
		return 0;
	return 1;
}


// trazimo cvor u uredjenom stablu
Node* findInOrdered(Node* root, int findValue) {
	if (!root)
		return NULL;
	if (root->value == findValue) return root;
	if (root->value > findValue)
		findInOrdered(root->left, findValue);
	else
		findInOrdered(root->right, findValue);
}

Node* findInUnordered(Node* root, int findValue) {
	if (!root)
		return NULL;
	if (root->value == findValue)
		return root;
	Node* node = findInUnordered(root->left, findValue);
	if (node)
		return node;
	else
		findInUnordered(root->right, findValue);
}

Node* addInOrdered(Node* root, int value) {
	if (!root)
		root = createNode(value);
	else if (root->value > value) {
		root->left = addInOrdered(root->left, value);
	}
	else if (root->value < value) {
		root->right = addInOrdered(root->right, value);
	}
	else if (rand() % 2)
		root->left = addInOrdered(root->left, value);
	return root;
}

Node* addInUnordered(Node* root, int value) {
	if (!root)
		root = createNode(value);
	else if (rand() % 2)
		root->left = addInUnordered(root->left, value);
	else
		root->right = addInUnordered(root->right, value);
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
	printf("%d", root->value);
	print2D(root->left, space);
}

Node* addNinOrdered(int n) {
	int k;
	Node* root = NULL;
	for (int i = 0; i < n; i++) {
		scanf("%d", &k);
		root = addInOrdered(root, k);
	}
	return root;
}

Node* addNinUnordered(int n) {
	int k;
	Node* root = NULL;
	for (int i = 0; i < n; i++) {
		scanf("%d", &k);
		root = addInUnordered(root, k);
	}
	return root;
}

Node* readOrderedFromFile(char* name) {
	FILE* f = fopen(name, "r");
	int k;
	Node* root = NULL;
	while (!feof(f)) {
		scanf("%d", &k);
		root = addInOrdered(root, k);
	}
	return root;
}

Node* readUnorderedFromFile(char* name) {
	FILE* f = fopen(name, "r");
	int k;
	Node* root = NULL;
	while (!feof(f)) {
		scanf("%d", &k);
		root = addInUnordered(root, k);
	}
	return root;
}

Node* freeTree(Node* root) {
	if (root) {
		root->left = freeTree(root->left);
		root->right = freeTree(root->right);
		free(root);
		root = NULL;
	}
	return root;
}

Node* deleteNodeInOrdered(Node* root, int value) {
	if (root) {
		if (root->value > value)
			// kao temp = temp->next->doSmt()
			root->left = deleteNodeInOrdered(root->left, value);
		else if (root->value < value)
			root->right = deleteNodeInOrdered(root->right, value);
		// idemo levo ili desno dok ne naidjemo na vrenost koja je value 
		//kad naidjemo pitamo se da li postoji levi ili desni
		else if (root->left) {
			int maxi = maximal_o(root->left);
			root->value = maxi;
			root->left = deleteNodeInOrdered(root->left, maxi);
		}
		else if (root->right) {
			int mini = minimal_o(root->right);
			root->value = mini;
			root->right = deleteNodeInOrdered(root->right, mini);
		}
		//dosli smo do lista
		else {
			free(root);
			root = NULL;
		}
	}
	return root;
}

Node* deleteNodeInUnordered(Node* root, int value) {
	if (root) {
		if (root->value == value) {
			if (root->left) {
				root->value = root->left->value;
				root->left = deleteNodeInUnordered(root->left, root->value);
			}
			else if (root->right) {
				root->value = root->right->value;
				root->right = deleteNodeInUnordered(root->right, root->value);
			}
			else {
				free(root);
				root = NULL;
			}
		}
		// sada treba da kazemo gde da ide ako nije naiso na value
		else {
			int v = size(root->left);
			root->left = deleteNodeInUnordered(root->left, value);
			if (v == size(root->left))
				root->right = deleteNodeInUnordered(root->right, value);
		}
	}
	return root;
}


int main() {
	return 0;
}




