/*
52. Napisati funkciju koja će na osnovu ulaznih stekova stek1 i stek2 stvoriti novi stek 
koristeći pritom sledeće pravilo da se za novi element u novom steku uvek odabere manji 
od elemenata na vrhu stekova stek1 i stek2. 
Ukoliko se jedan od stekova isprazni, onda uzeti preostale elemente iz drugog. Ulazni stekovi moraju
nakon završetka funkcije ostati nepromenjeni. Funkcija mora imati prototip 
Stek *spoji(Stek *stek1,Stek *stek2);
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
		return INT_MAX;
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
		printf("\nStack is empty, there is nothing to pop out");
		return;
	}
	Stack* temp = *top;
	int val = peek(*top);
	*top = (*top)->link;
	free(temp);
	return val;
}

void clearStack(Stack** top) {
	while (*top){
		pop(top);
	}
}

void printStack(Stack* top) {
	while(top) {
		printf("| %d |\n", peek(top));
		top = top->link;
	}
	printf("\n");
}



Stack* spoji(Stack* top1, Stack* top2) {
	Stack* top3 = NULL;

	while (top1 || top2) {
		if (peek(top1) > peek(top2))
			push(pop(&top2), &top3);
		else {
			push(pop(&top1), &top3);
		}
	}

	return top3;
}

int main() {
	Stack* top1 = NULL;
	push(4, &top1);
	push(6, &top1);
	push(2, &top1);
	push(9, &top1);
	push(1, &top1);

	printStack(top1);

	Stack* top2 = NULL;
	push(7, &top2);
	push(6, &top2);
	push(5, &top2);
	push(9, &top2);
	push(3, &top2);

	printStack(top2);

	Stack* top3 = NULL;
	top3 = spoji(top1, top2);

	printStack(top3);

	return 0;
}