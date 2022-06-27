
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct zapis {
	long broj;
	struct zapis* sledeci;
	struct zapis* prethodni;
}Zapis;


Zapis* upis_iz_fajla(char text[]) {
	FILE* f = fopen(text, "r");
	Zapis* head = NULL;
	Zapis* trenutni = NULL;
	while (!feof(f)) {
		Zapis* novi = (Zapis*)malloc(sizeof(Zapis));
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

void pisi(Zapis* head) {
	if (!head) {
		printf("\nNe mozemo da prikazemo elemente jer nema elemenata u listi!");
	}
	while (head) {
		printf("| %d |   ", head->broj);
		head = head->sledeci;
	}
}

int duzina(Zapis* head) {
	int broj = 0;
	while (head) {
		broj++;
		head = head->sledeci;
	}
	return broj;
}

Zapis* nadji_kraj(Zapis* head) {
	while (head->sledeci) {
		head = head->sledeci;
	}
	return head;
}

int izbaciN(Zapis** head, Zapis** butt, int n) {
	int size = duzina(*head);
	Zapis* trenutni = NULL;
	if (size <= n) {
		while (*head) {
			trenutni = *head;
			*head = (*head)->sledeci;
			free(trenutni);
		}
		return size;
	}
	else {
		for (int i = 0; i < n; i++) {
			trenutni = (*butt);
			trenutni->prethodni->sledeci = NULL;
			(*butt) = trenutni->prethodni;
			free(trenutni);
		}
		return n;
	}

}

int main() {

	Zapis* head = upis_iz_fajla("032zad.txt");
	Zapis* butt = nadji_kraj(head);
	pisi(head);
	int n;
	printf("\nKoliko elemenata brises: ");
	scanf("%d", &n);
	int b = izbaciN(&head, &butt, n);
	if (b != n) {
		printf("Izbrisali smo sve elemente jer je broj elemenata koji zelite da brisete veci od ukupnog broja elemenata  (%d > %d) ", n, b);
		pisi(head);
	}
	else {
		printf("\nIzbrisali smo %d elemenata iz liste\nNova lista:   ", n);
		pisi(head);
	}
	printf("\n");

	return 0;

}