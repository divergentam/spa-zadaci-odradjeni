/*
23. Stringove možemo prikazati kao vezanu listu, čije ćelije su zapisi sa dve komponente: znak,
pointer na iduću ćeliju. Napišite potrebnu definiciju tipa podatka STRING. Zatim napišite
potprogram koji proverava da li su dva ovako implementirana stringa jednaka, i ako nisu,
vraća pointer na prvu ćeliju u drugom stringu u kojoj se pojavljuje razlika.
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct string {
	char znak;
	struct string* link;
}String;

void pisi(String* head) {
	while (head) {
		printf("%c", head->znak);
		head = head->link;
	}
	printf("\n");
}

void upisi(FILE* f, String** s1, String** s2) {
	String* nova = NULL, *poslednji = NULL;
	char c;
	while (1) {
		fscanf(f, "%c", &c);
		if (c == '\n') {
			break;
		}
		nova = (String*)malloc(sizeof(String));
		nova->znak = c;
		nova->link = NULL;
		if (!poslednji) {
			*s1 = nova;
		}
		else {
			poslednji->link = nova;
		}
		poslednji = nova;
	}
	poslednji = NULL;
	while (!feof(f)) {
		fscanf(f, "%c", &c);
		nova = (String*)malloc(sizeof(String));
		nova->znak = c;
		nova->link = NULL;
		if (!poslednji) {
			*s2 = nova;
		}
		else {
			poslednji->link = nova;
		}
		poslednji = nova;
	}
}

String* uporedi(String* s1, String* s2) {
	while (s1 && s2) {
		if (s1->znak != s2->znak) {
			return s2;
		}
		s1 = s1->link;
		s2 = s2->link;
	}
	return NULL;
}


int main() {
	String* s1 = NULL;
	String* s2 = NULL;
	FILE* f = fopen("023zad.txt", "r");

	upisi(f, &s1, &s2);
	pisi(s1);
	pisi(s2);
	String* razlika = uporedi(s1, s2);
	if (razlika == NULL) {
		printf("Stringovi su isti");
	}
	else {
		pisi(razlika);
	}


	fclose(f);
	return 0;
}
