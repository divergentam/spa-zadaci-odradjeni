/*
60. Napišite nerekurzivan potprogram int SQ(QUEUE *Q) koji pretražuje red od početka do kraja, i pritom
izbacuje duplikate elemenata koji su se već pre pojavili u redu. Uz to, broji koliko puta se koji element pojavio
u redu i vraća najveći takav broj. Međusobni redosled ostalih (neizbačenih) elemenata ostaje nepromenjen.
Pretpostavljamo da je na podacima tipa elementtype definisano uređenje “<=”. Potprogram treba biti
nezavisan od implementacije atp QUEUE;
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue {
	int broj;
	struct queue* link;
}Queue;

void push(int broj, Queue** top, Queue** butt) {
	Queue* novi = (Queue*)malloc(sizeof(Queue));
	if (novi == NULL) {
		printf("Queue overflow!");
		exit(1);
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

int pop(Queue** top, Queue** butt) {
	if ((*top == *butt) && butt == NULL) {
		printf("Nema elemenata za delete, queue je prazan!");
		return -46249;
	}
	Queue* temp = NULL;
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

void ucitaj(char text[], Queue** top, Queue** butt) {
	FILE* f = fopen(text, "r");
	int val;
	while (!feof(f)) {
		fscanf(f, "%d", &val);
		push(val, top, butt);
	}
}

bool isElem(int x, Queue** top, Queue** butt) {
	bool postoji = false;
	Queue* pomt = NULL, * pomb = NULL;
	int prvi;
	while (*top) {
		prvi = pop(top, butt);
		if (x == prvi)
			postoji = true;
		push(prvi, &pomt, &pomb);
	}
	*top = pomt;
	*butt = pomb;

	return postoji;
}

int izbaci_duple(Queue** top, Queue** butt, int* broj) {
	int val, i = 0, brojac;
	while (*top) {
		val = pop(top, butt);
		if ((*top)->broj == val) {
			brojac++;
		}
	}

}

int main() {
	Queue* top = NULL, * butt = NULL;
	ucitaj("060zad.txt", &top, &butt);
	printQueue(top);

	int broj, maxpon;
	maxpon = izbaci_duple(&top, &butt, &broj);
	printQueue(top);

	printf("Broj %d se pojavljuje %d puta ( najvece pojavljivanje ) ", broj, maxpon);

	return 0;
}

