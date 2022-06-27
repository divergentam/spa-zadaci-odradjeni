/*
30. Dat je pokazivac na prvi element dvostruko spregnute liste ciji elementi predstavljaju
elemente reči (slovo ili prazno mesto). Napisati metodu koja proverava da li je data recenica
(rec) palindrom. Palindrom je rec (recenica) koja se cita isto s obe strane (i sleva na desno i
s desna na levo)
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct elem {
	char slovo;
	struct elem* sledeci;
	struct elem* prethodni;
}Elem;

Elem* upisi_iz_fajla_head(char text[]) {
	FILE* f = fopen(text, "r");
	char c;
	Elem* head = NULL, * trenutni = head;
	while ((c = fgetc(f)) != EOF) {
		Elem* novi = (Elem*)malloc(sizeof(Elem));
		novi->slovo = c;
		novi->slovo = toupper(novi->slovo);
		if (novi->slovo != ' ') {
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
	}
	return head;
}

//Elem* upisi_iz_fajla_naopako(char text[]) {
//	FILE* f = fopen(text, "r");
//	fseek(f, 0, SEEK_SET);
//	char c;
//	Elem* head = NULL, * trenutni = head;
//	while ((c = fgetc(f)) != EOF) {
//		Elem* novi = (Elem*)malloc(sizeof(Elem));
//		novi->slovo = c;
//		novi->slovo = toupper(novi->slovo);
//		if (novi->slovo != ' ') {
//			novi->sledeci = NULL;
//			if (!trenutni) {
//				novi->prethodni = NULL;
//			}
//			else {
//				novi->sledeci = head;
//				trenutni->prethodni = novi;
//			}
//			head = novi;
//			trenutni = novi;
//		}
//	}
//	return head;
//}


void pisi(Elem* head) {
	while (head) {
		printf("%c", head->slovo);
		head = head->sledeci;
	}
	printf("\n");
}

Elem* nadji_kraj(Elem* head) {
	while (head->sledeci) {
		head = head->sledeci;
	}
	return head;
}

bool uporedi(Elem* head, Elem* butt) {
	while (head != butt) {
		if (head->slovo != butt->slovo) {
			return false;
		}
		head = head->sledeci;
		butt = butt->prethodni;
	}
	return true;
}

int main() {
	Elem* head = upisi_iz_fajla_head("030zad.txt");
	Elem* butt = nadji_kraj(head);
	pisi(head);
	
	if (uporedi(head, butt))
		printf("Palindrom");
	else
		printf("Nije palindrom");

	return 0;
}