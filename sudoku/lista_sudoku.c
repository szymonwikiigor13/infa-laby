#define _CRT_SECURE_NO_WARNINGS

#include "lista_sudoku.h"
#include "sudoku.h"

#include <stdlib.h>
#include <stdio.h>

lista_sudoku_ptr lista_sudoku_nowa() {
	lista_sudoku_ptr lista = (lista_sudoku_ptr)malloc(sizeof(struct lista_sudoku));
	if (lista == NULL) return NULL;

	lista->sudoku = NULL;
	lista->poprzedni = NULL;
	lista->nastepny = NULL;

	return lista;
}

void lista_sudoku_zwolnij(lista_sudoku_ptr lista) {
	lista_sudoku_ptr temp = lista;

	while (temp->poprzedni != NULL) temp = temp->poprzedni; // przejscie do poczatku listy

	while (temp->nastepny != NULL) { // dopoki wskaznik nie jest na ostatnim elemencie
		if (temp->sudoku != NULL) {
			sudoku_zwolnij(temp->sudoku);
		}

		temp = temp->nastepny;
		free(temp->poprzedni);
	}

	if (temp->sudoku != NULL) {
		sudoku_zwolnij(temp->sudoku);
	}

	free(temp);
}

void lista_sudoku_dodaj(lista_sudoku_ptr lista, sudoku_ptr sudoku) {
	lista_sudoku_ptr temp = lista;

	while (temp->nastepny != NULL) temp = temp->nastepny; // idziemy na koniec listy

	if (temp->sudoku == NULL) {
		temp->sudoku = sudoku;
	}
	else {
		temp->nastepny = lista_sudoku_nowa();

		temp->nastepny->sudoku = sudoku;
		temp->nastepny->poprzedni = temp;
	}
}

void lista_sudoku_wypisz(lista_sudoku_ptr lista) {
	lista_sudoku_ptr temp = lista;

	while (temp->poprzedni != NULL) temp = temp->poprzedni;

	int licznik = 1;
	while (temp != NULL) {
		printf("Sudoku numer %d\n", licznik++);

		if (temp->sudoku == NULL) {
			printf("Sudoku jest puste");
		}
		else {
			sudoku_wypisz(temp->sudoku);
		}

		temp = temp->nastepny;
		printf("\n");
	}
}

void wczytaj_sudoku_z_pliku(lista_sudoku_ptr lista, char* sciezka) {
	FILE* plik = fopen(sciezka, "r");
	if (plik == 0) return;

	int bufor;

	while (!feof(plik)) {
		sudoku_ptr sudoku = sudoku_nowe();

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				fscanf(plik, "%d,", &bufor);

				sudoku->plansza[i][j] = bufor;
			}
		}

		lista_sudoku_dodaj(lista, sudoku);
	}

	fclose(plik);
}

int lista_sudoku_rozmiar(lista_sudoku_ptr lista) {
	lista_sudoku_ptr temp = lista;

	while (temp->poprzedni != NULL) temp = temp->poprzedni;

	int licznik = 1;
	while (temp != NULL) {
		temp = temp->nastepny;
		licznik++;
	}

	return licznik;
}

sudoku_ptr lista_sudoku_indeks(lista_sudoku_ptr lista, int indeks) {
	lista_sudoku_ptr temp = lista;

	while (temp->poprzedni != NULL) temp = temp->poprzedni;

	int licznik = 1;
	while (temp != NULL) {
		if (indeks == licznik) {
			return temp->sudoku;
		}

		temp = temp->nastepny;
		licznik++;
	}

	return NULL;
}