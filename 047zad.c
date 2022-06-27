/*
47. Napisati funkciju koja će iz steka izbaciti sva pojavljivanja broja n.
Funkcija mora u novi stek, koji je inicijalno prazan, ubaciti brojeve koji 
predstavljaju koliko je broj bio udaljen od originalnog vrha steka. Funkcija ima
sledeći prototip: void izbaci_broj(Stek *stek, int n, Stek *novi);
*/

#ifdef _MSC_VER 
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER 

#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	int broj;
	struct stack* link;
}Stack;

int isEmpty(Stack* top) {
	if (top == NULL)
		return 1;
	return 0;
}

void push(int broj, Stack** top) {
	Stack* novi = (Stack*)malloc(sizeof(Stack));
	novi->broj = broj;
	novi->link = (*top);
	(*top) = novi;
}

int pop(Stack** top) {
	if (isEmpty(top)) {
		printf("Stack je prazan!");
		return 0;
	}
	else {
		int vrednost = (*top)->broj;
		Stack* trenutni = (*top);
		(*top) = (*top)->link;
		free(trenutni);
		return vrednost;
	}
}

void printStack(Stack* top) {
	while (top) {
		printf("| %d |\n", top->broj);
		top = top->link;
	}
	printf("\n");
}

void ucitaj_stack(char text[], Stack** top) {
	FILE* f = fopen(text, "r");
	int broj;
	while (!feof(f)) {
		fscanf(f, "%d", &broj);
		push(broj, top);
	}
}

void izbaci_broj(Stack** top, int n, Stack** novi) {
	Stack* temp = NULL;
	int brojac = 0;
	while (*top) {
		if ((*top)->broj == n) {
			push(brojac, novi);
		}
		else {
			push((*top)->broj, &temp); //dakle ako broj nije n onda ga pamtimo u drugi stack
		}
		pop(top); // taj el izbacujemo iz prvobitnog stack
		brojac++;
	}
	while (temp) {
		push(temp->broj, top);
		pop(&temp);
	}
}

int main() {
	int n;
	Stack* top = NULL;
	Stack* novi = NULL;
	ucitaj_stack("047zad.txt", &top);
	printStack(top);
	printf("Unesite broj koji hocete da izbacite iz stack-a : ");
	scanf("%d", &n);
	izbaci_broj(&top, n, &novi);
	printStack(top);
	printStack(novi);

	return 0;
}