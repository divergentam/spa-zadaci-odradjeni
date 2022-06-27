
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
		fscanf(f, "%d", &novi->broj);
		novi->sledeci = NULL;
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


void pisi_levo(Elem* head, Elem* p) {
	while (head && head != p) {
		printf("|  %d  | -> <-  ", head->broj);
		head = head->sledeci;
	}
	printf("|  %d  | ", head->broj);

	printf("\n");
}

void pisi(Elem* head) {
	while (head && head->sledeci != NULL) {
		printf("|  %d  | -> <-  ", head->broj);
		head = head->sledeci;
	}
	printf("|  %d  | ", head->broj);

	printf("\n");
}

void resi(Elem* head, Elem* p) {
	Elem* butt = nadji_kraj(head);
	Elem* desni = p->sledeci; // kad ispitujem desnu stranu krecem od pointer->link do kraja
	Elem* levi = head;// kad ispitujem levu stranu krecem od head-a do pointera

	int suma_desni = 0;
	int suma_levi = 0;

	if (p == head) {
		return pisi(head); // vracamo celu desnu
	}
	if (p == butt) {
		return pisi_levo(head, butt); //vracamo celu levu
	}

	while (desni) {
		suma_desni += desni->broj;
		desni = desni->sledeci;
	}
	printf("\nSuma desno : %d", suma_desni);
	while (levi && levi->sledeci != p->sledeci) {
		suma_levi += levi->broj;
		levi = levi->sledeci;
	}
	printf("\nSuma levo : %d\n", suma_levi);

	if (suma_desni > suma_levi) {
		pisi(p);
	}
	else {
		pisi_levo(head, p);
	}

}

Elem* odredi_pointer(Elem* head, int n) {
	for (int i = 1; i < n; i++) {
		head = head->sledeci;
	}
	return head;
}

int main() {
	Elem* head = upis_iz_fajla("029zad.txt");
	pisi(head);

	Elem* butt = nadji_kraj(head);
	Elem* p = odredi_pointer(head,4);
	printf("Pokazujem na broj %d", p->broj);
	resi(head, p);

	return 0;
}