/*
44. Napisati program u programskom jeziku C koji koristeći ADT stack učitava tekst 
iz fajla ulaz.txt i ispisuje u fajl izlaz.txt reč po reč unazad.
Reči su nizovi karaktera odvojeni simbolima: space, tab, newline
*/

#ifdef  _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif //  _MSC_VER

#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	char c;
	struct stack* link;
}Stack;

void push(char c, Stack** top) {
	Stack* novi = (Stack*)malloc(sizeof(Stack));
	if (novi == NULL) {
		printf("Stack overflow!");
	}
	novi->c = c;
	novi->link = *top;
	*top = novi;
}

char pop(Stack** top) {
	if (*top == NULL) {
		printf("Stack je prazan, nema el za izbacivanje");
		return '/';
	}
	Stack* temp = *top;
	char c = (*top)->c;
	*top = (*top)->link;
	free(temp);
	return c;
}

void ucitaj(char text1[], char text2[], Stack** top) {
	FILE* f1 = fopen(text1, "r");
	FILE* f2 = fopen(text2, "w");
	char ch;
	Stack* pom = NULL;
	while ((ch = fgetc(f1)) != EOF) {
		if (ch == ' ' || ch == '\t' || ch == '\n') {
			while (pom != NULL) {
				fprintf(f2, "%c", pop(&pom));
			}
			fprintf(f2, "%c", ch); // upisujemo u space || newline || tab
		}
		else {
			push(ch, &pom); //ako ch nije ' ' || '\t\ || '\n' onda ubacujemo ch u pomocni stack
		}
	}
	while (pom != NULL) {
		fprintf(f2, "%c", pop(&pom));
	}
}



int main() {

	Stack* top = NULL;
	ucitaj("R050zad.txt", "W050zad.txt", &top);
	//nema potrebe za brisanjem stacka jer je on obrisan prilikom ispisa u izlazni fajl

	return 0;
}