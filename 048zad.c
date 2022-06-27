/*
48. Posmatrajmo implementaciju “dinamičkog” steka pomoću polja promenljive dužine. 
Pretpostavimo da će stek sadržati celobrojne podatke. Potrebno je napisati 
funkcije za stavljanje elementa na stek i skidanje elementa sa steka. 
Ako na steku nema mesta za novi element, stek treba dinamički povećati za 
10 novih mesta (i upisati novi element). Takođe, kod skidanja elementa sa steka potrebno
je proveriti koliko praznog mesta ima na steku.
Ako ima više od 10 praznih mesta, veličinu steka potrebno je smanjiti za 10.
Funkcije trebaju vratiti 1 ako je operacija uspela, a 0 inače. Napišite i deklaraciju tipa podatka STACK.
*/

#ifdef _MSC_VER 
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER 

#include <stdio.h>
#include <stdlib.h>

void isEmpty(int* niz) {
	if (niz == NULL)
		return 1;
	return 0;
}

void isFull(int* niz) {}

void push(int broj, int** niz) {}

int main() {
	int* niz = NULL;

	return 0;
}