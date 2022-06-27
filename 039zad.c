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


void upis_iz_fajla(char text[], Zapis** head1, Zapis** head2) {
	FILE* f = fopen(text, "r");
	Zapis* head = NULL;
	Zapis* trenutni = NULL;
	int n;
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {
		Zapis* novi = (Zapis*)malloc(sizeof(Zapis));
		novi->sledeci = NULL;
		fscanf(f, "%d", &novi->broj);
		if (!trenutni) {
			novi->prethodni = NULL;
			(*head1) = novi;
		}
		else {
			trenutni->sledeci = novi;
			novi->prethodni = trenutni;
		}
		trenutni = novi;
	}
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {
		Zapis* novi = (Zapis*)malloc(sizeof(Zapis));
		novi->sledeci = NULL;
		fscanf(f, "%d", &novi->broj);
		if (!trenutni) {
			novi->prethodni = NULL;
			(*head2) = novi;
		}
		else {
			trenutni->sledeci = novi;
			novi->prethodni = trenutni;
		}
		trenutni = novi;
	}
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

Zapis* nadji_kraj(Zapis* head) {
	while (head->sledeci) {
		head = head->sledeci;
	}
	return head;
}


int main() {
	Zapis* head1 = NULL;
	Zapis* head2 = NULL;
	upis_iz_fajla("02zad.txt", &head1, &head2);
	Zapis* butt1 = nadji_kraj(head1);
	Zapis* butt2 = nadji_kraj(head2);
	pisi(head1);
	pisi(head2);
	

	return 0;

}