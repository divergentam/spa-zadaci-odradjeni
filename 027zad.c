#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct polinom {
	double koeficijent;
	long stepen1;
	long stepen2;
	struct polinom* link;
}Polinom;



Polinom* dodaj(Polinom* polinom, double koeficijent, long stepen1, long stepen2) {
	Polinom* c, * novi, * prethodni = NULL;

	c = polinom;
	while (c && c->stepen1 > stepen1 && c->stepen2 > stepen2) {
		prethodni = c;
		c = c->link;
	}
	if (!c || c->stepen1 > stepen1 || c->stepen2 > stepen2)) {
	novi = (Polinom*)malloc(sizeof(Polinom));
	novi->stepen1 = stepen1;
	novi->stepen2 = stepen2;
	novi->link = c;
	novi->koeficijent = koeficijent;
	if (!prethodni) {
		polinom = novi;
	}
	else {
		prethodni->link = novi;
	}
	return polinom;
	}
	if (c->stepen1 == stepen1 && c->stepen2 == stepen2) {
		c->koeficijent += koeficijent;
	}
	return polinom;
}

Polinom* napravi_polinom() {
	int stepen;
	double c;
	Polinom* p = NULL;


	return p;
}

void printPolinom(Polinom* p) {
	Polinom* temp = p;
	int znak = 1;
	while (temp) {
		if (temp->koeficijent < 0)
			znak = -1;
		znak = 1;
		printf("%c %2.f * x^%d * y^%d", znak * fabs(temp->koeficijent), temp->stepen1, temp->stepen2);
		temp = temp->link;
	}
}

void brisi(Polinom* p) {
	Polinom* temp;
	while (p) {
		temp = p;
		p = p->link;
		free(temp);
	}
}

Polinom* sabiranje(Polinom* p1, Polinom* p2) {
	Polinom* p, * novi = NULL; p = p1;
	while (p) {
		novi = dodaj(novi, p->koeficijent, p->stepen1, p->stepen2);
		p = p->link;
	}
	p = p2;
	while (p) {
		novi = dodaj(novi, p->koeficijent, p->stepen1, p->stepen2);
		p = p->link;
	}
	return novi;
}

int main() {


	return 0;
}