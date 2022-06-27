/*
U datoteci zad4.in u provm redu su dati brojevi n i m koji predstavljaju
dužine dva ulazna niza. U narednih n + m redova su dati elementi ta dva niza. 
Učitati nizove iz datoteke i napisati program koji objedinjuje ta dva niza u treći,
dužine n+m. Ulazni nizovi su sortirani u rastućem poretku. Neophodno je da i 
novoformirani niz bude sortiran u rastućem poretku. 
Zabranjeno je sortirati niz nakon formiranja. 
Rezultujući niz upisati u datoteku zad4.out i to tako što ćete u 
prvom redu zapisati dužinu niza, a u ostalim redovima članove niza.
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

void ucitaj_u_rastucem(int niz[], int tduzina, int vrednost) {
	int i = tduzina - 1;
	while (niz[i] > vrednost && i >= 0) {
		niz[i + 1] = niz[i];
		i--;
	}
	niz[i + 1] = vrednost;
}

void ucitaj_niz(int niz[], int n, FILE *f) {
	int tduzina = 0, vrednost;
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &vrednost);
		ucitaj_u_rastucem(niz, tduzina, vrednost);
		tduzina++;
	}
}

void ispisiniz(int niz[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", niz[i]);
	}
	printf("\n");
}

void spoji_nizove(int niz[], int niz1[], int niz2[], int n, int m, int *p) {
	for (int i = 0; i < n; i++) {
		niz[i] = niz1[i];
	}
	*p = n;
	for (int i = 0; i < m; i++) {
		ucitaj_u_rastucem(niz, *p , niz2[i]);
		(* p)++;
	}
}

int main() {
	int niz[20];
	int niz1[10];
	int niz2[10];
	int n, m, p;

	FILE *f = fopen("008zad.txt", "r");
	fscanf(f, "%d%d", &n, &m);

	ucitaj_niz(niz1, n, f);
	ucitaj_niz(niz2, m, f);
	spoji_nizove(niz, niz1, niz2, n, m, &p);

	fclose(f);

	ispisiniz(niz1, n);
	ispisiniz(niz2, m);
	ispisiniz(niz, p);

	return 0;
}