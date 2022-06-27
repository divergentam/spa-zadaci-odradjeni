/*
15. Napisati funkciju koja iz zadane liste u koju se zapisuju 
celi brojevi (int) brise parne elemente.
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
	int broj;
	struct elem* link;
}Elem;


void pisi(Elem* list) {
	if (!list) {
		printf("Lista je prazna");
		return;
	}
	while (list) {
		printf("\t| %d |    ", list->broj);
		list = list->link;
	}
}


Elem* na_kraj(Elem* list, int broj) {
	Elem* trenutni; // mora da postoji da se ne bi izgubio pocetak liste
	Elem* novi = (Elem*)malloc(sizeof(Elem));
	//postavljamo vrednosti za novi el
	novi->broj = broj;
	novi->link = NULL;
	if (!list) // ako je lista prazna i nema el
		return novi; //head postaje novi
	trenutni = list;
	while (trenutni->link) { //trazim kraj liste
		trenutni = trenutni->link;
	}
	trenutni->link = novi; //kad ga nadjem povezem ga da pokazuje na novi
	return list;
}


Elem* briseparne(Elem* head) {
	Elem* prethodni = NULL;
	Elem* trenutni = head;
	while (trenutni) {
		if (trenutni->broj % 2 == 0) {
			if (!prethodni) { //ako nije prethodni
				head = head->link;
				free(trenutni);
				trenutni = head;
			}
			else {
				prethodni->link = trenutni->link;
				free(trenutni);
				trenutni = prethodni->link;
			}
		}
		else {
			prethodni = trenutni;
			trenutni = prethodni->link;
		}
	}
	return head;
}


int main() {
	Elem* prvi = NULL;
	prvi = na_kraj(prvi, 10);
	prvi = na_kraj(prvi, 10);
	prvi = na_kraj(prvi, 6);
	prvi = na_kraj(prvi, 5);
	prvi = na_kraj(prvi, 65);	
	prvi = na_kraj(prvi, 61);
	prvi = na_kraj(prvi, 60);
	pisi(prvi);
	printf("\n");
	prvi = briseparne(prvi);
	pisi(prvi);

	return 0;
}