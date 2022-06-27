/*
20. Napisati program koji dodaje cvor u listi nakon cvora sa zadatom vrednoscu. U prvom redu
datoteke zad1.in je zadat broj n koji označava broj elemenata liste.
U narednih n redova je dato n celih brojeva koji će predstavljati elemente liste. 
U narednom redu je zadat broj m iza cijeg prvog pojavljivanja je potrebno dodati 
broj k koji se nalazi u poslednjem redu datoteke.
Ukoliko se broj m ne nalazi u listi, broj k dodati na početak liste. Rezultujuću listu zapisati u
datoteku zad1.out
*/

#ifdef  _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif //  _MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

Elem* na_pocetak(Elem* head, int broj) {
	Elem* novi = (Elem*)malloc(sizeof(Elem));
	novi->broj = broj;
	novi->link = head;
	head = novi;
}

Elem* iz_fajla(FILE* f, int *m, int *k) {
	Elem* head = NULL;
	Elem* novi, * poslednji = NULL;
	int n;

	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {
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

	fscanf(f, "%d", m);
	fscanf(f, "%d", k);

	return head;
}

Elem* upisi(Elem* head, int m, int k) {
	Elem* trenutni = head;

	bool nasao_m = false;
	while (trenutni) {
		if (trenutni->broj == m) {
			Elem* novi = (Elem*)malloc(sizeof(Elem));
			novi->broj = k;
			novi->link = trenutni->link;
			trenutni->link = novi;
			trenutni = novi->link;
			nasao_m = true;
		}
		else {
			trenutni = trenutni->link;
		}
	}

	if (!nasao_m) {
		head = na_pocetak(head, k);
	}

	return head;
}

void ispisi_u_fajl(Elem* head, FILE* f) {
	while (head) {
		fprintf(f, " | %d |    ", head->broj);
		head = head->link;
	}
}

int main() {
	int m, k;
	FILE* f1 = fopen("R020zad.txt", "r");
	FILE* f2 = fopen("W020zad.txt", "w");

	Elem* head = iz_fajla(f1, &m, &k);
	fclose(f1);
	pisi(head);

	printf("Posle broja %d upisi %d\n", m, k);
	head = upisi(head, m, k);
	ispisi_u_fajl(head, f2);
	fclose(f2);

	return 0;
}