/*
21. Dati su brojevi d, m, n i jednostruko povezana lista celih brojeva. Naći broj podlisti date liste,
sastavljene od susednih elemenata početne liste koje su dužine m, a zbir elemenata podliste
je jednak d. U prva dva reda ulazne datoteke zad1.in se nalaze brojevi d i m, a u narednom
redu n, dok se u narednih n redova nalazi n celih brojeva koji predstavljaju elemente liste.
Rezultat zapisati u datoteku zad1.out.
*/


#ifdef  _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif //  _MSC_VER

#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
	int broj;
	struct elem* link;
}Elem;

Elem* upisi_iz_fajla(FILE* f, int* d, int* m, int* n) {
	Elem* head = NULL, *prethodni = NULL;

	fscanf(f, "%d%d%d", d, m, n);

	while (!feof(f)) {
		Elem* novi = (Elem*)malloc(sizeof(Elem));
		novi->link = NULL;
		fscanf(f, "%d", &novi->broj);
		if (!prethodni) {
			head = novi;
		}
		else {
			prethodni->link = novi;
		}
		prethodni = novi;

	}
	return head;
}

void ispisi(Elem* head) {
	while (head) {
		printf("|  %d  |     ", head->broj);
		head = head->link;
	}
	printf("\n");
}

int broj_podlisti(Elem* head, int d, int m) {
	int brojac = 0, zbir = 0;
	Elem* pom = NULL;
	while (head) {
		pom = head;
		for (int i = 0; i < m; i++) {
			if (pom == NULL) {  // pitamo za pom jer ce pom u poslednjem koraku da uzme vrednost head = head-> link; koji ce na poslenjem el da ima vrednost null
				zbir = d + 1; // bilo koj zbor != od d // TO JE KAD JE PODLISTA KRATKA TAKO DA NE MOZE DA UZME M EL
				break; //izlazimo iz svega
			}
			zbir += pom->broj;
			pom = pom->link;
		}
		if (zbir == d) {
			brojac++;
		}
		head = head->link;
		zbir = 0;
	}
	return brojac;
}

int main() {
	FILE* f = fopen("021zad.txt", "r");
	int d, n, m;
	Elem* head = upisi_iz_fajla(f, &d, &m, &n);
	ispisi(head);

	printf("Broj podlisti gde je zbir %d elemenata jednak %d je : %d ", m, d, broj_podlisti(head, d,m));

	return 0;
}