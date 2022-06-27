/*
58. Napisati u programskom jeziku C program koji, koristeći ADT Queue, 
iz fajla ulaz.txt u fajl izlaz.txt prepisuje prvo pojavljivanje karaktera
redom kojim se pojavljuju (ignoriše duplikate).
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue {
	int broj;
	struct queue* link;
}Queue;

void insert(int broj, Queue** top, Queue** butt) {
	Queue* novi = (Queue*)malloc(sizeof(Queue));
	if (novi == NULL) {
		printf("Queue overflow");
		return;
	}
	novi->broj = broj;
	novi->link = NULL;
	if (!(*butt)) {
		*butt = novi;
		*top = *butt;
	}
	else {
		(*butt)->link = novi;
		*butt = novi;
	}
}

int delete(Queue** top, Queue** butt) {
	if ((*top == *butt) && *butt == NULL) {
		printf("Nema elemenata za delete, queue je prazan!");
		return -46249;
	}
	Queue* temp = *top;
	int val = (*top)->broj;
	*top = (*top)->link;
	if (*top == NULL)
		*butt = (*butt)->link;
	free(temp);
	return val;
}

void printQueue(Queue* top) {
	if (!top) {
		printf("Queue je prazan!");
	}
	while (top) {
		printf("| %d |\n", top->broj);
		top = top->link;
	}
	printf("\n");
}

bool isElem(int x, Queue** top, Queue** butt) {
	bool postoji = false;
	Queue* pomt = NULL, * pomb = NULL;
	int prvi;
	while (*top) {
		prvi = delete(top, butt);
		if (prvi == x)
			postoji = true;
		insert(prvi, &pomt, &pomb);

	}
	*top = pomt;
	*butt = pomb;

	return postoji;
}

void ucitaj(char text[], Queue** top, Queue** butt) {
	FILE* f = fopen(text, "r");
	int val;
	while (!feof(f)) {
		fscanf(f, "%d", &val);
		if (!(isElem(val, top, butt))) {
			insert(val, top, butt);
		}
	}
}

int main() {
	Queue* top = NULL, * butt = NULL;
	ucitaj("058zad.txt", &top, &butt);
	printQueue(top);

	return 0;
}