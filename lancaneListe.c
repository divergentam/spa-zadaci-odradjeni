#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
	int broj;
	struct  elem* link;
}Elem;

int duzina(Elem* list) {
	int n = 0;
	while (list) {
		n++;
		list = list->link;
	}
	return n;
}

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

Elem* na_pocetak(Elem* list, int broj) {
	Elem* novi = (Elem*)malloc(sizeof(Elem*));
	novi->broj = broj;
	novi->link = list; // da pointer novog el pokazuje na adresu prethodnog prvog el
	list = novi; // list nam je pokazivac i on sad sadrzi adresu novog el 
	return list;
}

Elem* na_kraj(Elem* list, int broj) {
	Elem* trenutni; // mora da postoji da se ne bi izgubio pocetak liste
	Elem* novi = (Elem*)malloc(sizeof(Elem));
	//postavljamo vrednosti za novi el
	novi->broj = broj;
	novi->link = NULL;
	if (!list) // ako je lista prazna i nema el
		return novi;
	trenutni = list;
	while (trenutni) {
		if (trenutni->link) {
			trenutni = trenutni->link;
		}
		else {
			trenutni->link = novi;
			return list;
		}
	}
}

Elem* dodaj_elemente_na_pocetak(int n) {
	Elem* list = NULL;
	printf("Unesite %d elemenata liste (svaki novi el se dodaje na pocetak liste): ", n);
	for (int i = 0; i < n; i++) {
		Elem* novi = (Elem*)malloc(sizeof(Elem));
		scanf("%d", &novi->broj);
		novi->link = list;
		list = novi;
	}
	return list;
}

Elem* dodaj_elemente_na_kraj(int n) {
	Elem* list = NULL;
	Elem* trenutni = NULL;
	printf("Unesite %d elemenata liste (svaki novi el se dodaje na kraj liste): ", n);
	for (int i = 0; i < n; i++) {
		Elem* novi = (Elem*)malloc(sizeof(Elem));
		scanf("%d", &novi->broj);
		novi->link = NULL;
		if (!list)
			list = novi;
		else {
			trenutni->link = novi;
		}
		trenutni = novi;
	}
	return list;
}

Elem* umetni_u_uredjenu_listu(Elem* list, int broj) {
	Elem* trenutni = list, * prethodni = NULL, * novi;

	if (trenutni) {
		if (trenutni->broj >= broj) {
			return novi = na_pocetak(list, broj);
		}
	}
	else {
		return novi = na_pocetak(list, broj);
	}

	while (trenutni && trenutni->broj < broj) {
		prethodni = trenutni;
		trenutni = trenutni->link;
	}
	novi = (Elem*)malloc(sizeof(Elem));
	novi->broj = broj;
	if (!prethodni) {
		list = novi;
	}
	else {
		prethodni->link = novi;
		novi->link = trenutni;
	}
	return list;
}

//void delociraj(Elem* prvi) {
//	Elem* stari = NULL;
//	while (prvi) {
//		stari = prvi;
//		prvi = prvi->link;
//		free(stari);
//	}
//	prvi = NULL;
//}

Elem* izostavi(Elem* list, int broj) {
	Elem* trenutni = list, * prethodni = NULL, * stari;

	while (trenutni) {
		if (trenutni->broj != broj) {
			prethodni = trenutni;
			trenutni = trenutni->link;
		}
		else {
			stari = trenutni;
			trenutni = trenutni->link;
			if (!prethodni) {
				list = trenutni;
			}
			else {
				prethodni->link = trenutni;
			}
			free(stari);
		}
	}
	return list;

}

int main() {
	Elem* prvi = NULL;
	prvi = na_kraj(prvi, 5);
	prvi = na_pocetak(prvi, 10);
	prvi = na_kraj(prvi, 15);
	prvi = na_kraj(prvi, 5);

	Elem* novi = NULL;
	novi = na_pocetak(novi, 2);
	novi = umetni_u_uredjenu_listu(novi, 1);
	novi = umetni_u_uredjenu_listu(novi, 4);
	novi = umetni_u_uredjenu_listu(novi, 8);
	novi = umetni_u_uredjenu_listu(novi, 5);


	pisi(prvi);
	printf("Duzina: %d\n", duzina(prvi));
	prvi = izostavi(prvi, 5);
	printf("\n");
	prvi = na_kraj(prvi, 52);
	pisi(prvi);

	printf("\n");
	pisi(novi);

	//delociraj(novi);

	return 0;
}