/* Napisati metodu koja pravi istovetnu kopiju date liste.
 Lista je zadata standardno u datoteci.
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
	int broj;
	struct elem* link;
}Elem;

void pisi(Elem* head) {
	while (head) {
		printf("| %d |    ", head->broj);
		head = head->link;
	}
	printf("\n");
}

Elem* upisi_iz_fajla(FILE* f) {
	Elem* head = NULL, * poslednji = NULL;
	while (!feof(f)) {
		Elem* novi = (Elem*)malloc(sizeof(Elem));
		novi->link = NULL;
		fscanf(f, "%d", &novi->broj);
		if (!head) {
			head = novi;
		}
		else {
			poslednji->link = novi;
		}
		poslednji = novi;
	}
	return head;
}

Elem* kopiraj(Elem* head) {
	Elem* kopija = NULL, *poslednji = NULL;
	if (!head) {
		printf("Lista je prazna , nemamo sta da iskopiramo! ");
		return head;
	}
	while (head) {
		Elem* novi = (Elem*)malloc(sizeof(Elem));
		novi->link = NULL;
		novi->broj = head->broj;
		if (!kopija) {
			kopija = novi;
		}
		else {
			poslednji->link = novi;
		}
		poslednji = novi;
		head = head->link;
	}
	return kopija;
}


int main() {
	FILE* f = fopen("017zad.txt", "r");
	Elem* head = upisi_iz_fajla(f);
	fclose(f);
	pisi(head);
	Elem* kopija = kopiraj(head);
	pisi(kopija);
	return 0;
}

