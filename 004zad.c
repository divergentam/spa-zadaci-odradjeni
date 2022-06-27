/*
* U provom redu ulazne datoteke se nalazi broj članova, 
a u svakom narednom po jedan član niza. 
Napisati funkciju int prosekParnih(int niz[]) koja računa i
vraća prosek parnih elemenata niza (onih koji imaju parne vrednosti, 
a ne na parnim mestima u nizu).
*/


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

float prosekParnih(int niz[], int n) {
	int sum = 0, br_parnih = 0;
	for (int i = 0; i < n; i++) {
		if (niz[i] % 2 == 0) {
			sum += niz[i];
			br_parnih++;
		}
	}
	return (float) sum / br_parnih;
}

int main() {
	int n, vrednost;
	int niz[100];
	FILE* f = fopen("004zad.txt", "r");

	fscanf(f, "%d", &n);

	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &niz[i]);
	}

	fclose(f);

	printf("Prosek parnih clanova niza je: %f", prosekParnih(niz, n));



	return 0;
}

