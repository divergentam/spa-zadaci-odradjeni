/*13. Napisati rekurzivnu funkciju koja ce u jednostruko spregnutoj 
linearnoj listi prebrojati pozitivne elemente.*/


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>


typedef struct elem {
	int broj;
	struct elem* link;
}Elem;


int broj_pozitivnih(Elem* head) {
	if (head) {
		(head->broj > 0) ? 1 + broj_pozitivnih(head->link) : broj_pozitivnih(head->link);
	}
	else {
		return 0;
	}
}


Elem* dodaj_u_listu_kraj(FILE* f) {
	Elem* prvi = NULL, * poslednji = NULL; //pokazivac poslednji pokazuje na poslednji el
	int i;
	while (!feof(f)) {
		Elem* novi = (Elem*)malloc(sizeof(Elem));
		fscanf(f, "%d", &novi->broj);
		novi->link = NULL; //novi el je poslednji
		if (!prvi) prvi = novi; //ako je lista prazna
		else {
			poslednji->link = novi; // da pokazuje na poslednji el liste
		}
		poslednji = novi;
	}
	return prvi;
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
	FILE* f = fopen("013zad.txt", "r");
	Elem* list = NULL;
	
	list = dodaj_u_listu_kraj(f);
	pisi(list);
	printf("\nBroj pozitivnih elemenata je : %d", broj_pozitivnih(list));
	fclose(f);
	return 0;
}

