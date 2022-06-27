/*
24. Jednostruko povezana lista u memoriji sadrži statističke podatke o svim dosadašnjim
nastupima jednog tenisera na turnirima. Element liste sadrži šifru turnira (int) i broj pobeda
na tom turniru (int). Napisati rekurzivnu funkciju koja će vratiti ukupan broj pobeda tog
tenisera na svim turnirima. Prototip funkcije je zadat i nije ga dozvoljeno mijenjati:
									int broj_pobeda(cvor *glava);
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct turnir {
	int sifra;
	int brojpobeda;
	struct turniri* link;
}Turnir;

//int broj_pobeda(Turnir* t1) {
//	int odgovor;
//	printf("Da li hocete da unesete novi turnir? (1 - da, 0 - ne): ");
//	scanf("%d", &odgovor);
//	if (odgovor == 1) {
//		Turnir* t1 = (Turnir*)malloc(sizeof(Turnir));
//		printf("Unesite sifru turnira: ");
//		scanf("%d", &t1->sifra);
//		printf("Unesite broj pobeda za turnir: ");
//		scanf("%d", &t1->brojpobeda);
//		return t1->brojpobeda + broj_pobeda(t1);
//	}
//	else return 0;
//}

Turnir* upisi_iz_fajla(FILE* f) {
	Turnir* teniser = NULL, * poslednji = NULL;;

	while (!feof(f)) {
		Turnir* novi = (Turnir*)malloc(sizeof(Turnir));
		novi->link = NULL;
		fscanf(f, "%d%d", &novi->sifra, &novi->brojpobeda);
		if (!poslednji) {
			teniser = novi;
		}
		else {
			poslednji->link = novi;
		}
		poslednji = novi;
	}

	return teniser;
}

void pisi(Turnir* teniser) {
	if (!teniser) {
		printf("Lista je prazna! ");
	}
	while (teniser) {
		printf("|  %d  |  %d  |        ", teniser->sifra, teniser->brojpobeda);
		teniser = teniser->link;
	}
}

int broj_pobeda(Turnir* teniser) {
	while (teniser) {
		return broj_pobeda(teniser->link) + teniser->brojpobeda;
	}
	return 0;
}

int main() {
	/*Turnir* t1 = NULL;
	printf("Ukupan broj pobeda tenisera je: %d", broj_pobeda(t1));*/
	FILE* f = fopen("024zad.txt", "r");
	Turnir* teniser = upisi_iz_fajla(f);
	pisi(teniser);
	printf("\nBroj pobeda tenisera je : %d", broj_pobeda(teniser));

	return 0;
}