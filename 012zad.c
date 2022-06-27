/*Napisati program koji u jednostruko povezanoj linearnoj listi pronalazi i izbacuje element
koji se nalazi nakon elementa sa najmanjom vrednoscu*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
	int broj;
	struct elem* link;
}Elem;

int minimum(Elem* head) {
	int min = INT_MAX;
	if (head == NULL) {
		printf("Ne postoji niz! GRESKA!");
		exit(EXIT_FAILURE);
	}
	while (head) {
		if (head->broj < min) {
			min = head->broj;
		}
		head = head->link;
	}
	return min;
}
void izbaci(Elem* head) {
	if (!head) {
		printf("Nemamo sta da izbacimo!");
		exit(EXIT_FAILURE);
	}
	int min = minimum(head);
	Elem* naredni = NULL;
	while (head) {
		if (head->broj == min && head->link != NULL) {
			naredni = head->link;
			head->link = head->link->link;
			free(naredni);
		}
		head = head->link;
	}
}

Elem* dodaj_u_listu_kraj (FILE *f) {
	Elem* head = NULL;
	Elem* trenutni = head;
	while(!feof(f)){
		Elem* novi = (Elem*)malloc(sizeof(Elem));
		fscanf(f, "%d", &novi->broj);
		novi->link = NULL;
		if (!head) {
			head = novi;
		}
		else {
			trenutni->link = novi;
		}
		trenutni = novi;
	}
	return head;
}



void pisi(Elem* head) {
	if (!head) {
		printf("Lista nema elemenata");
		return;
	}
	while (head) {
		printf("| %d |   ", head->broj);
		head = head->link;
	}
}

int main() {
	FILE* f = fopen("012zad.txt", "r");
	Elem* list = NULL;

	list = dodaj_u_listu_kraj(f);
	pisi(list);
	printf("\n");
	izbaci(list);
	pisi(list);

	fclose(f);
	return 0;
}