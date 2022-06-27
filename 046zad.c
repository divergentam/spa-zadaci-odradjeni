/*
46. Napisati program koji proverava da li su html tagovi u datom HTML fajlu dobro upareni, koristeći stek.
*/

#ifdef  _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif //  _MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX 100

typedef struct stack {
	char tag[MAX];
	struct stack* link;
}Stack;

int isEmpty(Stack* top) {
	if (top == NULL)
		return 1;
	else return 0;
}

void push(Stack** top, char* tag) {
	if (strlen(tag) >= MAX) {
		fprintf(stderr, "Etiketa koju pokusavamo staviti na stek preduga.\n");
		exit(1);
	}
	Stack* novi = (Stack*)malloc(sizeof(Stack));
	strcpy(novi->tag, tag);
	novi->link = *top;
	*top = novi;
}

int pop(Stack** top, char* tag) {
	if (isEmpty(top))
		return 0;
	strcpy(tag, (*top)->tag);
	Stack* temp = *top;
	*top = (*top)->link;
	free(temp);
	return tag;
}

void printStack(Stack* top) {
	while (top) {
		printf("| %d |\n", top->tag);
		top = top->link;
	}
}

void brisiStack(Stack** top) {
	Stack* temp = NULL;
	while (*top) {
		temp = *top;
		*top = (*top)->link;
		free(temp);
	}
}

int ucitaj(char text[]) {
	FILE* f = fopen(text, "r");
	Stack* top = NULL;
	Stack* ime = NULL;
	char* tag1;
	while ((tag1 = fgetc(f)) != EOF) {
		if (tag1 == '<') {
			push(&top, tag1); // ubacujemo u stack da je tag otvoren
		}
		else if (isalpha(tag1)) {
			
		}
	}
}

int main() {
	ucitaj("046zad.txt");
}