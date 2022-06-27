/*
45. Napisati algoritam za proveru ispravnosti postavljenih zagrada u fajlu. 
Koristiti stek kao strukturu podataka za čuvanje otvorenih zagrada
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

int isEmpty(Stack* top) {
	if (top == NULL)
		return 1;
	else return 0;
}

void push(int c, Stack** top) {
	Stack* novi = (Stack*)malloc(sizeof(Stack));
	novi->c = c;
	novi->link = *top;
	*top = novi;
}

int pop(Stack** top) {
	if (isEmpty(top)) {
		printf("Stack je prazan nema elenta za izbacivanje!");
		return 0;
	}
	Stack* temp = *top;
	int val = (*top)->c;
	*top = (*top)->link;
	free(temp);
	return val;
}

int validate(char text[]) {
	FILE* f = fopen(text, "r");
	Stack* top = NULL;
	char ch, ch1;
	while ((ch = fgetc(f)) != EOF) {
		if (ch == '(' || ch == '{' || ch == '[') {
			push(ch, &top);
		}
		else 
			if (ch == ')' || ch == '}' || ch == ']') {
				if (isEmpty(top))
					return 2;
				else {
					ch1 = pop(&top);
					if (ch1 == '(' && ch != ')')
						return 3;
					if (ch1 == '{' && ch != '}')
						return 4;
					if (ch1 == '[' && ch != ']')
						return 5;
				}
			}
	}
	if (!(isEmpty(top)))
		return 1;

	return 0;
}

int main() {

	printf("Znacenje vracenog koga:\n");
	printf("0 - Zagrade su ispravno postavljene.\n");
	printf("1 - Neka otvorena zagrada nije zatvorena.\n");
	printf("2 - Zatvorena zagrada nije prethodno otvorena.\n");
	printf("3 - Pokusaj zatvaranja zagrade '(' nekim drugim tiom\n");
	printf("4 - Pokusaj zatvaranja zagrade '{' nekim drugim tiom\n");
	printf("5 - Pokusaj zatvaranja zagrade '[' nekim drugim tiom\n\n");

	printf("Validnost zagrada je: %d", validate("045zad.txt"));

	return 0;
}