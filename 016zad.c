/* Napisati funkciju koja na osnovu zadate liste pravi drugu,
 sa elementima u obrnutom redosledu u odnosu na prvu.
 Lista se zadaje u datoteci na standardni nacin.
*/


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

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
}

Elem* na_pocetak(Elem* head, int broj) {
	Elem* novi = (Elem*)malloc(sizeof(Elem));
	novi->broj = broj;
	novi->link = head;
	head = novi;

	return head;
}

Elem* invertuj(Elem* head) {
	Elem* nova = NULL;
	while (head) {
		nova = na_pocetak(nova, head->broj);
		head = head->link;
	}
	return nova;
}

Elem* upisi_iz_fajla(FILE * f) {
	Elem* head = NULL, *poslednji = NULL;
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


int main() {
	FILE* f = fopen("016zad.txt", "r");

	Elem* head = upisi_iz_fajla(f);
	fclose(f);
	pisi(head);
	printf("\n");
	Elem* inverzna = invertuj(head);
	pisi(inverzna);

	return 0;
}