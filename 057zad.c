#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

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
	if (*butt == NULL) {
		*top = *butt;
	}
	else {
		(*butt)->link = novi;
	}
	*butt = novi;
}

int delete(Queue** top, Queue** butt){
	if ((*top == *butt) && *butt == NULL) {
		printf("Red je prazan, nema brisanja!");
		return -49841;
	}
	int val = (*top)->broj;
	Queue* temp = *top;
	*top = (*top)->link;
	free(temp);
	return val;
}

void printQueue(Queue* top) {
	while (top) {
		printf("| %d |\n", top->broj);
		top = top->link;
	}
	printf("\n");
}

void ucitaj(char text[], Queue** top, Queue** butt) {
	FILE* f = fopen(text, "r");
	int val;
	while (!feof(f)) {
		fscanf(f, "%d", &val);
		insert(val, top, butt);
	}
}

int main() {
	Queue* top = NULL, * butt = NULL;
	ucitaj("057zad.txt", &top, &butt);
	printQueue(top);
	delete(&top, &butt);
	printf("Nakon delete (brise el sa pocetka): \n");
	printQueue(top);

	return 0;
}