
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

Elem* dodaj(int broj, Elem* head) {
	Elem* butt = NULL;
	Elem* novi = (Elem*)malloc(sizeof(Elem));
	novi->broj = broj;
	novi->sledeci = NULL;
	if (!head) {
		head = novi;
		novi->prethodni = NULL;
		return head;
	}
	butt = head;
	while (butt->sledeci) {
		butt = butt->sledeci;
	}
	butt->sledeci = novi;
	novi->prethodni = butt;

	return head;
}



Elem* upis_iz_fajla(char text[]) {
	FILE* f = fopen(text, "r");
	Elem* head = NULL;
	Elem* trenutni = NULL;


	while(!feof(f)) {
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

void pisi(Elem* head) {
	if (!head) {
		printf("\nNe mozemo da prikazemo elemente jer nema elemenata u listi!");
	}
	while (head) {
		printf("| %d |   ", head->broj);
		head = head->sledeci;
	}
	printf("\n");
}

bool isElem(int x, Elem* head1) {
	bool postoji = false;

	while (head1) {
		if (head1->broj == x) {
			postoji = true;
		}
		head1 = head1->sledeci;
	}

	return postoji;
}

Elem* razlika(Elem* head1, Elem* head2) {
	Elem* pom = NULL;
	int val;
	Elem* temp1 = head1, * temp2 = head2;
	while (temp2) {
		val = temp2->broj;
		if (!(isElem(val, temp1)) && (!(isElem(val, pom)))) {
			pom = dodaj(val, pom);
		}	
		temp2 = temp2->sledeci;
	}
	while (head1) {
		val = head1->broj;
		if (!(isElem(val, head2)) && (!(isElem(val, pom)))) {
			pom = dodaj(val, pom);
		}
		head1 = head1->sledeci;
	}

	return pom;
}

void pisi_fajl(Elem* raz, char text[]) {
	FILE* f = fopen(text, "w");
	while (raz) {
		fprintf(f, "| %d |   ", raz->broj);
		raz = raz->sledeci;
	}
}

int main() {
	Elem* head1 = upis_iz_fajla("038zad.txt");
	Elem* head2 = upis_iz_fajla("038zad2.txt");
	pisi(head1);
	pisi(head2);
	Elem* raz = razlika(head1, head2);
	pisi_fajl(raz, "W038zad.txt");
}