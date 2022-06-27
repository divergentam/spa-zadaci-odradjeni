/*11. Napisati C program koji vraca broj ponavljanja zadate vrednosti u listi.*/

#ifdef  _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
	int broj;
	struct elem* link;
}Elem;

Elem* dodaj_element(Elem* head, int broj) {
	Elem* novi = (Elem*)malloc(sizeof(Elem));
	novi->broj = broj;
	novi->link = head;
	head = novi;
	return head;
}

int br_ponavljanja(Elem* head, int vrednost) {
	int i = 0;
	while (head) {
		if (head->broj == vrednost) {
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
		printf("| %d |   ", head->broj);
		head = head->link;
	}
}

int main() {

	Elem* list = NULL;

	list = dodaj_element(list, 5);
	list = dodaj_element(list, 10);
	list = dodaj_element(list, 7);
	list = dodaj_element(list, 10);
	list = dodaj_element(list, 2);
	list = dodaj_element(list, 10);

	pisi(list);
	printf("\nBroj ponavljanja elementa 10 u listi je : %d\n", br_ponavljanja(list, 10));

	return 0;
}