/*
26. NCP koji iz neprazne datoteke broj.txt ucitava paran broj celih brojeva x[1], x[2],...,x[n], gde
n nije unapred poznato. Ispisati poruku na standardni izlaz da li vazi da
x[1]==x[n], x[2]==x[n1],..., x[k]=x[n-k+1], k=1..n/2
*/

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
	Elem* trenutni = NULL;
	while (!feof(f)) {
		Elem* novi = (Elem*)malloc(sizeof(Elem));
		novi->sledeci = NULL;
		fscanf(f, "%d", &novi->broj);
		if (!trenutni) {
			novi->prethodni = NULL;
			head = novi;
		}
		else {
			trenutni->sledeci = novi;
			novi->prethodni = trenutni;
		}
		trenutni = novi;
	}
	return head;
}

Elem* nadji_kraj(Elem* head) {

	while (head->sledeci) {
		head = head->sledeci;
	}
	return head;
}

bool resi(Elem* head) {
	Elem* butt = nadji_kraj(head);
	while (head != butt->prethodni) { //dokle god ne dodjemo do 
		if (head->broj != butt->broj) {
			return false;
		}
		head = head->sledeci;
		butt = butt->prethodni;
	}
	return true;
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

	head = upis_iz_fajla("026zad.txt");

	pisi(head);
	if (resi(head) == 0)
		printf("Jednakost ne vazi");
	else 		
		printf("Jednakost vazi");


	return 0;
}
