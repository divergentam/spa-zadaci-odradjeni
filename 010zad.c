/*10. Napisati C program koji ce vratiti koliko elemenata liste ima vrednost vecu od elementa na
pocetku liste.*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
	int broj;
	struct elem* link;
}Elem;

Elem* dodaj_elem(Elem* head, int broj) {
	Elem* novi = (Elem*)malloc(sizeof(Elem));
	novi->broj = broj;
	novi->link = head;
	head = novi;
	return head;
}

int br_el_vecih_od(Elem* head) {
	int pocetna_vrednost, i = 0;
	if (head) {
		pocetna_vrednost = head->broj;
		head = head->link;
	}
	while (head) {
		if(head->broj > pocetna_vrednost){
			i++;
		}
		head = head->link;
	}
	return i;
}

void pisi(Elem* head) {
	if (!head) {
		printf("Lista nema elemenata");
		return;
	}

	while (head) {
		printf("| %d |     ", head->broj);
		head = head->link;
	}
}


int main() {

	Elem* list = NULL;

	list = dodaj_elem(list, 5);
	list = dodaj_elem(list, 1);
	list = dodaj_elem(list, 7);
	list = dodaj_elem(list, 10);
	list = dodaj_elem(list, 2);


	pisi(list);
	printf("Broj elemenata koji imaju vecu vrednost od %d je %d", list->broj, br_el_vecih_od(list));

	return 0;
}