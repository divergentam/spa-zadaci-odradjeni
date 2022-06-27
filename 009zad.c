
/*
Napisati C program koji pronalazi najveću dužinu povezanih elemenata 
matrice koje sadrže 1 u 0-1 matrici. Data je matrica koja za elemente 
ima 0 ili 1. Kaže se da su dva elementa povezana ako su jedan do drugog 
horizontalno, vertikalno ili dijagonalno.
U jednoj matrici može biti više povezanih regiona. 
Ulaz: 
	  1 1 0 0 0				Izlaz: 5 
	  0 1 1 0 0 
	  0 0 1 0 1
	  1 0 0 0 1
	  0 1 0 1 1

Ideja: Za svaki element pretraži svih 8 pravaca i nastaviti 
pretragu u pravcima gde se povećava broj 1-ca.
*/


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

// mat[i][j] = *(*(mat+i)+j)

//kad se pristupa dinamickom nizu/matrice automatski se deferencira
ucitaj(int** mat, int n, int m, FILE* f) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fscanf(f, "%d", &mat[i][j]); // (*(mat+i)+j)
		}
	}
}

ispisi(int** mat, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", mat[i][j]); // *(*(mat+i)+j)
		}
		printf("\n");
	}
}

void ispitajHorizontalu(int** mat, int n, int m, int *max) {
	int novimax = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] == 1) {
				while (mat[i][j] == 1 && j < m) {
					novimax++;
					j++;
				}
				if (novimax > *max) {
					*max = novimax;
				}
			}
			novimax = 0;
		}
		novimax = 0;
	}
}

void ispitajVertikalu(int** mat, int n, int m, int* max) {
	int novimax;
	for (int j = 0; j < m; j++) {
		novimax = 0;
		for (int i = 0; i < n; i++) {
			if (mat[i][j] == 1) {
				while (mat[i][j] == 1) {
					novimax++;
					if (i == n - 1 && mat[i][j] == 1) // ovo pisemo da se ne bi javio nepostojevi index
						break;
					i++;
				}
				if (novimax > *max) {
					*max = novimax;
				}
			}
			novimax = 0;
		}
		novimax = 0;
	}
}

void ispitajGlavnuDijagonalu(int** mat, int n, int m, int* max) {
	/*
	1 0 0 0
	0 1 0 0
	0 0 1 0
	0 0 0 1
	*/
	int i = 0;
	for (int j = 0; j < m; j++) {
		i = 0;
		int c = j;
		while (i < n && c < m) {
			if (mat[i][c] == 1) {
				int p = i, k = c, novamax = 0;
				while (mat[p][k] == 1 && p < n && k < m) {
					novamax++;
					if (p == m - 1 && k == n - 1)
						break;
					p++; k++;
				}
				if (novamax > *max) {
					*max = novamax;
				}
				novamax = 0;
			}
			i++; c++;
		}
	}
}


void ispitajSporedneDijagonale(int** mat, int n, int m, int* max) {
	/*
	0 0 0 1
	0 0 1 0
	0 1 0 0
	1 0 0 0
	*/
	int i, j, novimax = 0;
	// gornji trougao + sporedna dijadonala
	for (int k = 0; k < m; k++) {
		i = k; // i ide od 0 pa do m
		j = 0; // j ide od 0 do
		if (mat[i][j] == 1) {
			while (i >= 0 && mat[i][j] == 1) {
				novimax++;
				i--;
				j++;
			}
		}
		if (novimax > *max)
			*max = novimax;
		novimax = 0;
	}
	// donji trougao - sporedna dijagonala
	for (int k = 1; k < n; k++) {
		i = m - 1; // i ide od m-1 do 0
		j = k; // j ide od 1 do n // da se ne bi duplirala sporedna dijagonala
		if (mat[i][j] == 1) {
			while (j < n && mat[i][j] == 1) {
				novimax++;
				i--;
				j++;
			}
		}
		if (novimax > *max)
			*max = novimax;
		novimax = 0;
	}
}

int ispitaj(int** mat, int n, int m) {
	int max = 0 ;
	//ispitajHorizontalu(mat, n, m, &max);
	//ispitajVertikalu(mat, n, m, &max);
	//ispitajSporedneDijagonale(mat, n, m, &max);
	ispitajGlavnuDijagonalu(mat, n, m, &max);

	return max;
}


int main() {
	int n, m;
	FILE* f = fopen("009zad.txt", "r");

	fscanf(f, "%d%d", &n, &m);
	int** mat = (int**)calloc(n, sizeof(int*));

	for (int i = 0; i < n; i++) {
		mat[i] = (int*)calloc(m, sizeof(int));
	}

	ucitaj(mat, n, m, f);
	fclose(f);
	ispisi(mat, n, m);

	printf("MAX je %d", ispitaj(mat, n, m));

	for (int i = 0; i < n; i++) {
		free(mat[i]);
	}
	free(mat);


	return 0;
}
