#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
	int broj;
	struct elem* link;
}Elem;

void pisi(Elem* head) {
	while (head) {
		printf("| %d |    ", head->broj);
		head = head->link;
	}
	printf("\n");
}

Elem* upisi_iz_fajla(FILE* f) {
	Elem* head = NULL, * poslednji = NULL;
	while (!feof(f)) {
		Elem* novi = (Elem*)malloc(sizeof(Elem));
		novi->link = NULL;
		fscanf(f, "%d", &novi->broj);
		if (!head) {
			head = novi;
			poslednji = novi;
		}
		else {
			poslednji->link = novi;
			poslednji = novi;
		}
	}
	return head;
}

void eleminisi(Elem** head, int x) {
	Elem* trenutni = (*head), * prethodni = NULL;
	if (!(* head)) {
		printf("Lista je prazna, broj %d se ne moze eliminisati!", x);
		return head;
	}
	while (trenutni) {
		if (!prethodni) {
			if (trenutni->broj == x) {
				(*head) = (*head)->link;
				free(trenutni);
				trenutni = (*head);
			}
		}
		if (trenutni->broj == x) {
			prethodni->link = trenutni->link;
			free(trenutni);
			trenutni = prethodni->link;
		}
		else {
			prethodni = trenutni;
			trenutni = trenutni->link;
		}		
	}
}

int main() {
	FILE* f = fopen("022zad.txt", "r");
	Elem* head = upisi_iz_fajla(f);
	fclose(f);
	pisi(head);
	eleminisi(&head, 6);
	pisi(head);

	return 0;
}
