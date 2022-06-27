#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct jsl {
	int broj;
	struct jl* link;
}Jsl;

typedef struct dsl {
	struct dsl* pokazuje;
	struct dsl* sledeci;
	struct dsl* prethodni;
}Dsl;


void pisi(Dsl* head) {
	while (head) {
		Jsl* headjsl = head->pokazuje;
		printf("%p ->", headjsl);
		while (headjsl) {
			printf("| %d |   ", headjsl->broj);
			headjsl = headjsl->link;
		}
		printf("\n");
		head = head->sledeci;
	}
}


int main() {
	Dsl* head = NULL;
	pisi(head);
	return 0;
}