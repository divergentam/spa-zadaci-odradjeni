/*
49. Napisati funkciju koja će iz steka izbaciti sve one brojeve koji se pojavljuju dva ili 
više puta. Funkcija ima sledeći prototip:
void izbaci_duple(Stek *stek);
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
	if (novi == NULL) {
		printf("Stack overflow!");
		return;
	}
	novi->broj = broj;
	novi->link = *top;
	*top = novi;
}

int pop(Stack** top) {
	if (isEmpty(*top))
		return -1;
	Stack* temp = *top;
	int vrednost = (*top)->broj;
	*top = (*top)->link;
	free(temp);
	return vrednost;
}

int peek(Stack* top) {
	if (isEmpty(top))
		return -1;
	return top->broj;
}


void printStack(Stack* top) {
	if (isEmpty(top))
		printf("Stack je prazan!");
	while (top) {
		printf("| %d |\n", peek(top));
		top = top->link;
	}
	printf("\n");
}

void ucitaj(char text[], Stack** top) {
	FILE* f = fopen(text, "r");
	int val;
	while (!feof(f)) {
		fscanf(f, "%d",&val);
		push(val, top);
	}
	fclose(f);
}

bool isElem(int x, Stack** top) {
	bool postoji = false;
	Stack* pom = NULL;
	int val;
	while (*top) {
		val = pop(top);
		if (x == val)
			postoji = true;
		push(val, &pom);
	}

	while (pom) {
		push(pop(&pom), top);
	}


	return postoji;
}


void izbaci_duple(Stack** top) {
	Stack* pom = NULL;
	int val;
	while (*top) {
		val = pop(top);
		if (! (isElem(val, &pom))) {
			push(val, &pom);
		}
	}

	while (pom) {
		push(pop(&pom), top);
	}
}

int main() {
	Stack* top = NULL;
	ucitaj("049zad.txt", &top);
	printStack(top);

	izbaci_duple(&top);
	printStack(top);

	return 0;
}