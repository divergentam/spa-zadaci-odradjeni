#ifdef _MSC_VER 
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER 

#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	int broj;
	struct stack* link;
}Stack;

void push(int broj, Stack** top) {
	Stack* novi = (Stack*)malloc(sizeof(Stack));
	novi->broj = broj;
	novi->link = (*top);
	(*top) = novi;
}

int pop(Stack** top) {
	if ((*top) == NULL) {
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

int main() {
	Stack* top = NULL;
	push(4, &top);
	push(8, &top);
	push(1, &top);
	push(7, &top);
	push(9, &top);
	push(3, &top);

	printStack(top);


	pop(&top);
	push(7, &top);
	pop(&top);
	pop(&top);
	pop(&top);
	push(4, &top);

	printStack(top);

	return 0;
}