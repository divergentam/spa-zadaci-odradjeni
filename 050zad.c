/*
50. Dat je stek S u kojem se čuvaju podaci tipa char. Na žalost, neki od elemenata 
steka su bombe (označene sa *).Napišite nerekurzivnu funkciju sa prototipom:
void makni_bombe(Stack **s)
koja će iz steka S ukloniti sve bombe, a ostale elemente poređati u ”naopakom” poretku. 
Na primer, ako su elementi u S redom od vrha prema dnu steka (*, D, *, C, B, A), 
onda nakon poziva funkcije stek treba izgledati ovako: (A, B, C, D).
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
		printf("Stack je prazan nema el za izbacivanje!");
		return '/';
	}
	Stack* temp = *top;
	char val = (*top)->c;
	*top = (*top)->link;
	free(temp);
	return val;
}

int peek(Stack *top) {
	if (top == NULL)
		return NULL;
	return top->c;
}

void ucitaj(char text[], Stack** top) {
	FILE* f = fopen(text, "r");
	char val;
	while ((val = fgetc(f)) != EOF) {
		if (val != ' ') {
			push(val, top);
		}
	}
	fclose(f);
}

void printStack(Stack* top) {
	while (top) {
		printf("| %c |\n", top->c);
		top = top->link;
	}
	printf("\n");
}

void makni_bombe(Stack** top) {
	Stack* pom = NULL;
	while (*top) {
		if (((*top)->c) != '*')
			push(pop(top), &pom);
		else
			pop(top);
	}
	*top = pom;
}

int main() {
	Stack* top = NULL;
	ucitaj("050zad.txt", &top);
	printStack(top);
	makni_bombe(&top);
	printf("Nakon uklanjanja bombi invertovan stack : \n");
	printStack(top);

	return 0;
}