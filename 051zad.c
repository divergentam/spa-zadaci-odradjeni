/*
51. U kontekstu strukture STACK napišite potprogram 
void INSERT_SECOND (int x, Stack** s)
koji ubacuje element x u stek S, tako da x bude drugi element odozdo (tj. drugi element od dna steka).
Međusobni redosled ostalih elemenata ostaje nepromenjen. Potprogram bi trebalo da bude nezavistan od
implementacije atp. STACK.
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	int broj;
	struct stack* link;
}Stack;

int peek(Stack* top) {
	if (top == NULL)
		return NULL;
	return top->broj;
}

void push(int broj, Stack** top) {
	Stack* novi = (Stack*)malloc(sizeof(Stack));
	if (novi == NULL) {
		printf("Stack overflow!");
		exit(EXIT_FAILURE);
	}
	novi->broj = broj;
	novi->link = *top;
	*top = novi;
}

int pop(Stack** top) {
	if (*top == NULL) {
		printf("Stack is empty, no elements for pop");
		return 0;
	}
	Stack* temp = *top;
	int val = peek(*top);
	*top = (*top)->link;
	free(temp);
	return val;
}

void printStack(Stack* top) {
	while (top) {
		printf("| %d |\n", peek(top));
		top = top->link;
	}
	printf("\n");
}

void clearStack(Stack** top) {
	while (*top) {
		pop(top);
	}
}

void ucitaj(char text[], Stack** top) {
	FILE* f = fopen(text, "r");
	int broj;
	while (!feof(f)) {
		fscanf(f, "%d", &broj);
		push(broj, top);
	}
}

void umetni_na_drugo_mesto(int x, Stack** top) {
	Stack* pom = NULL;
	while ((* top)->link) {
		push(pop(top), &pom);
	}
	push(x, &pom);
	push(pop(top), &pom);
	
	while (pom) {
		push(pop(&pom), top);
	}
}



int main() {
	Stack* top = NULL;
	ucitaj("051zad.txt", &top);
	printStack(top);
	umetni_na_drugo_mesto(2, &top);
	printStack(top);
	clearStack(&top);
	
	return 0;
}