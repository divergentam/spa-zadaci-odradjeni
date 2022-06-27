
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct elem {
	int broj;
	struct elem* prethodni;
	struct elem* sledeci;
}Elem;

Elem* upis_iz_fajla(char text[]) {
	FILE* f = fopen(text, "r");

	Elem* head = NULL;
	Elem* butt = NULL;

	Elem* prvibroj = (Elem*)malloc(sizeof(Elem));
	fscanf(f, "%d", &prvibroj->broj);
	prvibroj->sledeci = NULL;
	prvibroj->prethodni = NULL;

	if (!head) {
		head = prvibroj;
		butt = head; // nemamo vise el
	}

	while (!feof(f)) {
		Elem* novi = (Elem*)malloc(sizeof(Elem));
		fscanf(f, "%d", &novi->broj);
		novi->sledeci = NULL; // ne pokazuje ni na sta jer mozda necemo da imamo novi el
		novi->prethodni = butt; //pokazuje na poslednji dodati el
		butt->sledeci = novi;
		butt = novi;
	}
	return head;
}

Elem* nadji_kraj(Elem* head) {

	while (head->sledeci) {
		head = head->sledeci;
	}
	return head;
}

Elem* resi(Elem* head) {
	Elem* trenutni = head;
	Elem* maksimalni = head;
	Elem* butt = nadji_kraj(head);
	while (trenutni) {
		if (trenutni->broj > maksimalni->broj) {
			maksimalni = trenutni;
		}
		trenutni = trenutni->sledeci;
	}

	if (maksimalni == head) {
		return head;
	}

	if (maksimalni == butt) {
		maksimalni->prethodni->sledeci = NULL;
		maksimalni->prethodni = NULL;
		maksimalni->sledeci = head;
		head = maksimalni;
	}
	else{
		maksimalni->prethodni->sledeci = maksimalni->sledeci;
		maksimalni->sledeci->prethodni = maksimalni->prethodni;
		maksimalni->sledeci = head;
		head = maksimalni;
		maksimalni->prethodni = NULL;
	}

	return head;
}

void pisi(Elem* head) {
	while (head && head->sledeci != NULL) {
		printf("|  %d  | -> <-  ", head->broj);
		head = head->sledeci;
	}
	printf("|  %d  | ", head->broj);

	printf("\n");
}

int main() {
	Elem* head = NULL;
	Elem* butt = NULL;

	head = upis_iz_fajla("028zad.txt");
	pisi(head);
	head = resi(head);
	pisi(head);

	return 0;
}