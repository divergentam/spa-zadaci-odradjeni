
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>


void u_rastucem(int *niz, int tduzina, int vrednost) {
	int i = tduzina - 1;
	while (niz[i] > vrednost && i >= 0) {
		niz[i + 1] = niz[i];
		i--;
	}
	niz[i + 1] = vrednost;
}


void ucitaj(int* niz, int n, FILE* f) {
	int tduzina = 0, vrednost;
		
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &vrednost);
		u_rastucem(niz, tduzina, vrednost);
		tduzina++;
	}
}

void ispisi(int* niz, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", niz[i]);
	}
	printf("\n");
}

void spoji(int* niz, int* niz1, int n, int* niz2, int m, int* p) {
	// BINO JE DA P NIJE POKAZIVAC 

	for (int i = 0; i < n; i++) {
		niz[i] = niz1[i];
	}
	*p = n;
	for (int i = 0; i < m; i++) {
		u_rastucem(niz, *p, niz2[i]);
		(* p)++; //MNOGO BITNO prednost ima ++
	}
}

int broj_elemenata(FILE *f) {
	int vel = 0;
	int broj;
	while (fscanf(f, "%d", &broj) == 1)
		vel++;

	return vel - 1;
}

void proveri(int* niz, int *n, FILE* f) {
	int vel = broj_elemenata(f);
	if (vel != *n) {
		*n = vel;
		niz = (int*)realloc(niz, *n * sizeof(int));
	}

}

int main() {
	int n, m, p;
	FILE* f1 = fopen("008d.txt", "r");
	FILE* f2 = fopen("008d2.txt", "r");

	fscanf(f1, "%d", &n);
	fscanf(f2, "%d", &m);

	int* niz1 = (int*)calloc(n, sizeof(int)); //	inicjalno garbage values
	int* niz2 = (int*)calloc(m, sizeof(int)); //	inicijalno nule 
	int* niz = (int*)calloc(n + m, sizeof(int));

	ucitaj(niz1, n, f1);
	ucitaj(niz2, m, f2);
	spoji(niz, niz1, n, niz2, m, &p);

	/*
	fseek(f1, 0, SEEK_SET);
	fseek(f2, 0, SEEK_SET);
	proveri(niz1, &n, f1);
	proveri(niz2, &m, f2);
	*/

	fclose(f1);
	fclose(f2);

	ispisi(niz1, n);
	ispisi(niz2, m);
	ispisi(niz, p);

	return 0;
}