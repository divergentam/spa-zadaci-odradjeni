/*
14. Napisati funkciju koja ispisuje elemente zadate sortirane liste 
(u koju se zapisuju celi brojevi int) koji su manji od zadatog broja n.
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

Elem* na_pocetak(Elem* head, int broj) {
	while (head) {
		Elem* novi = (Elem*)malloc(sizeof(Elem));
		novi->broj = broj;
		novi->link = head;
		head = novi;
	}
	return head;
}

void pisi(Elem* list) {
	if (!list) {
		printf("Lista je prazna");
		return;
	}
	while (list) {
		printf("\t| %d |    ", list->broj);
		list = list->link;
	}
}

Elem* upisiSortirano(Elem* head, int broj) {
	Elem* tren = head, * pret = NULL;
	Elem* novi = (Elem*)malloc(sizeof(Elem));
	novi->broj = broj;
	while (tren && tren->broj < broj) {
		pret = tren;
		tren = tren->link;
	} //trazimo gde treba da upisemo el
	novi->link = tren;
	if (!pret) { //ako prethodni bude null onda na pocetak
		head = novi;
		return head;
	}
	else { 
		pret->link = novi;
	}
	return head;
}

void upisivanje_uz_uslov(Elem* head, int n) {
	FILE* f = fopen("014zad.txt", "r");
	int vrednost;
	while (!feof(f)) {
		fscanf(f, "%d", &vrednost);
		if (vrednost < n) {
			head = upisiSortirano(head, vrednost);
		}
	}

	pisi(head);

	fclose(f);
}

int main() {
	Elem* head = NULL;
	int n;
	printf("Unesite broj koji zelite da bude uslov za listu: ");
	scanf("%d", &n);
	upisivanje_uz_uslov(head, n);

	return 0;
}