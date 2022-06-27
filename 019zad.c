/*
19. Napisati program koji od date dve jednostruko spregnute liste pravi trecu koja predstavlja
uniju elemenata date dve liste.
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

Elem* na_pocetak(Elem* head, int broj) {
	Elem* novi = (Elem*)malloc(sizeof(Elem));
	novi->broj = broj;
	novi->link = head;
	head = novi;

	return head;
}

Elem* na_kraj(Elem* head, int broj) {
	Elem* novi = (Elem*)malloc(sizeof(Elem));
	novi->broj = broj;
	novi->link = NULL;
	if (!head) {
		head = novi;
		return head;
	}
	Elem* trenutni = head;
	while (trenutni) {
		if (trenutni->link == NULL) {
			trenutni->link = novi;
			return head;
		}
		else 
			trenutni = trenutni->link;
	}
}

void pisi(Elem* head) {
	if (!head) {
		printf("Lista nema elemenata! ");
		return;
	}
	while (head) {
		printf("| %d |    ", head->broj);
		head = head->link;
	}
	printf("\n");
}


Elem* unija(Elem* prva, Elem* druga) {
	Elem* treca = NULL;

	while (prva) {
		treca = na_kraj(treca, prva->broj);
		prva = prva->link;
	}
	while (druga) {
		treca = na_kraj(treca, druga->broj);
		druga = druga->link;
	}

	return treca;	
}

int main() {
	Elem* prva = NULL;
	prva = na_kraj(prva, 4);
	prva = na_kraj(prva, 8);
	prva = na_kraj(prva, 10);
	prva = na_kraj(prva, 5);
	pisi(prva);

	Elem* druga = NULL;
	druga = na_pocetak(druga, 4);
	druga = na_pocetak(druga, 8);
	druga = na_pocetak(druga, 10);
	druga = na_pocetak(druga, 5);

	pisi(druga);

	Elem* treca = unija(prva, druga);
	pisi(treca);

	return 0;
}