/*
18.	Metoda koja od JSListe pravi niz
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

int duzina(Elem* head) {
	int duzina = 0;
	while (head) {
		duzina++;
		head = head->link;
	}
	return duzina;
}

void pisi(Elem* head) {
	while (head) {
		printf("| %d |    ", head->broj);
		head = head->link;
	}
	printf("\n");
}

Elem* upisi_iz_fajla(FILE *f) {
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

int* transformisi(Elem* head) {
	int velicina = duzina(head);
	int* niz = (int*)calloc(velicina, sizeof(int));

	for (int i = 0; i < velicina; i++) {
		niz[i] = head->broj;
		head = head->link;
	}

	printf("Niz( %d ) :", velicina);
	for (int i = 0; i < velicina; i++) {
		printf("%d  ", niz[i]);
	}

	return niz;
}

int main() {
	FILE* f = fopen ("018zad.txt", "r");
	Elem* head = upisi_iz_fajla(f);
	fclose(f);
	pisi(head);
	int* niz = transformisi(head);

	return 0;
}