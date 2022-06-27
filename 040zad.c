/*
40. Dat je pokazivač na prvi element DS liste. Napisati metodu koja računa zbir elemenata koji
se ponavljaju. Primer: Ulaz 5 7 2 2 5 2 8 2 5 6. Rezultat je 5+2=7. U prvom redu datoteke
zad2.in je zadat broj n koji označava broj elemenata liste. Članovi liste su zadati u narednih
n redova ulazne datoteke. Traženi zbir zapisati u datoteku zad2.out
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

bool isElem(int x, Elem* head) {
	bool postoji = false;
	while (head) {
		if (head->broj == x)
			postoji = true;
		head = head->sledeci;
	}
	return postoji;
}

Elem* dodaj_na_kraj(int broj, Elem* head) {
	Elem* temp = head;
	Elem* novi = (Elem*)malloc(sizeof(Elem));
	novi->broj = broj;
	novi->sledeci = NULL;
	if (!temp) {
		head = novi;
		return head;
	}
	while (temp->sledeci) {
		temp = temp->sledeci;
	}
	temp->sledeci = novi;
	
	return head;
}

bool isDuplicate(Elem* head, int n) {
	if (!head) {
		return false;
	}
	head = head->sledeci;
	while (head) {
		if (head->broj == n)
			return true;
		head = head->sledeci;
	}
	return false;
}

int zbir_duplih(Elem* head) {
	Elem* pom = NULL;
	int val, sum = 0;
	while (head) {
		if (isDuplicate(head, head->broj) && !isElem(head->broj, pom)) {
			sum += head->broj;
			pom = dodaj_na_kraj(head->broj, pom);
		}
		head = head->sledeci;
	}
	return sum;
}

Elem* upisi_iz_fajla(char text[]) {
	FILE* f = fopen(text, "r");
	Elem* temp = NULL;
	Elem* head = NULL;
	while (!feof(f)) {
		Elem* novi = (Elem*)malloc(sizeof(Elem));
		novi->sledeci = NULL;
		fscanf(f, "%d", &novi->broj);
		if (!temp) {
			head = novi;
		}
		else {
			temp->sledeci = novi;
		}
		temp = novi;
	}
	return head;
}

void printList(Elem* head) {
	while (head) {
		printf("| %d |   ", head->broj);
		head = head->sledeci;
	}
	printf("\n");
}

int main() {
	Elem* head = NULL;
	head = upisi_iz_fajla("040zad.txt", head);
	printList(head);
	printf("Zbir duplih je: %d", zbir_duplih(head));

	return 0;
}