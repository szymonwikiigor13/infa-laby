#define _CRT_SECURE_NO_WARNINGS

#include "sudoku.h"

#include <stdlib.h>
#include <stdio.h>

sudoku_ptr sudoku_nowe() {
	sudoku_ptr nowy = (sudoku_ptr)malloc(sizeof(struct sudoku));
	if (nowy == NULL) return NULL;

	nowy->plansza = (int**)calloc(9, sizeof(int*));

	if (nowy->plansza == NULL) {
		free(nowy);
		return NULL;
	}

	for (int i = 0; i < 9; i++) {
		nowy->plansza[i] = (int*)calloc(9, sizeof(int));

		if (nowy->plansza[i] == NULL) {
			for (int j = i - 1; j >= 0; j--) {
				free(nowy->plansza[j]);
			}
			free(nowy->plansza);
			free(nowy);

			return NULL;
		}
	}

	return nowy;
}

void sudoku_zwolnij(sudoku_ptr sudoku) {
	if (sudoku == NULL) return;

	for (int i = 0; i < 9; i++) {
		free(sudoku->plansza[i]);
	}

	free(sudoku->plansza);

	free(sudoku);
}

void sudoku_wypisz(sudoku_ptr sudoku) {
	if (sudoku == NULL) return;

	int** p = sudoku->plansza;

	printf("    1 2 3  4 5 6  7 8 9  \n");
	printf("   ===================== \n");
	printf("1 ||%d|%d|%d||%d|%d|%d||%d|%d|%d||\n", p[0][0], p[0][1], p[0][2], p[0][3], p[0][4], p[0][5], p[0][6], p[0][7], p[0][8]);
	printf("2 ||%d|%d|%d||%d|%d|%d||%d|%d|%d||\n", p[1][0], p[1][1], p[1][2], p[1][3], p[1][4], p[1][5], p[1][6], p[1][7], p[1][8]);
	printf("3 ||%d|%d|%d||%d|%d|%d||%d|%d|%d||\n", p[2][0], p[2][1], p[2][2], p[2][3], p[2][4], p[2][5], p[2][6], p[2][7], p[2][8]);
	printf("   ===================== \n");
	printf("4 ||%d|%d|%d||%d|%d|%d||%d|%d|%d||\n", p[3][0], p[3][1], p[3][2], p[3][3], p[3][4], p[3][5], p[3][6], p[3][7], p[3][8]);
	printf("5 ||%d|%d|%d||%d|%d|%d||%d|%d|%d||\n", p[4][0], p[4][1], p[4][2], p[4][3], p[4][4], p[4][5], p[4][6], p[4][7], p[4][8]);
	printf("6 ||%d|%d|%d||%d|%d|%d||%d|%d|%d||\n", p[5][0], p[5][1], p[5][2], p[5][3], p[5][4], p[5][5], p[5][6], p[5][7], p[5][8]);
	printf("   ===================== \n");
	printf("7 ||%d|%d|%d||%d|%d|%d||%d|%d|%d||\n", p[6][0], p[6][1], p[6][2], p[6][3], p[6][4], p[6][5], p[6][6], p[6][7], p[6][8]);
	printf("8 ||%d|%d|%d||%d|%d|%d||%d|%d|%d||\n", p[7][0], p[7][1], p[7][2], p[7][3], p[7][4], p[7][5], p[7][6], p[7][7], p[7][8]);
	printf("9 ||%d|%d|%d||%d|%d|%d||%d|%d|%d||\n", p[8][0], p[8][1], p[8][2], p[8][3], p[8][4], p[8][5], p[8][6], p[8][7], p[8][8]);
	printf("   ===================== \n");
}

int sudoku_mozna_ruch(sudoku_ptr sudoku, int rzad, int kolumna, int wartosc) {
	for (int j = 0; j < 9; j++) { // sprawdzenie rzedu
		if (sudoku->plansza[rzad][j] == wartosc) {
			return 0;
		}
	}

	for (int i = 0; i < 9; i++) { // sprawdzenie kolumny
		if (sudoku->plansza[i][kolumna] == wartosc) {
			return 0;
		}
	}

	int rzad_okno = rzad - rzad % 3, kolumna_okno = kolumna - kolumna % 3;

	for (int i = 0; i < 3; i++) { // sprawdzamy powtorzenia w oknie 3x3
		for (int j = 0; j < 3; j++) {
			if (sudoku->plansza[i + rzad_okno][j + kolumna_okno] == wartosc) {
				return 0;
			}
		}
	}

	return 1; // bez konfliktow
}

int sudoku_solver(sudoku_ptr sudoku, int rzad, int kolumna) {
	if (rzad == 8 && kolumna == 9) { // sprawdzilismy wszystkie kolumny
		return 1;
	}

	if (kolumna == 9) { // skonczylismy sprawdzac rzad
		rzad++;
		kolumna = 0;
	}

	if (sudoku->plansza[rzad][kolumna] > 0) { // jesli wartosc jest wypelniona to omijamy komorke
		return sudoku_solver(sudoku, rzad, kolumna + 1);
	}

	for (int wartosc = 1; wartosc <= 9; wartosc++) { // sprawdzamy od 1 dla kazdej wartosci czy mozemy wykonac ruch
		if (sudoku_mozna_ruch(sudoku, rzad, kolumna, wartosc) == 1) {
			sudoku->plansza[rzad][kolumna] = wartosc;

			if (sudoku_solver(sudoku, rzad, kolumna + 1) == 1) { // rekurencyjnie sprawdzamy czy kolejna kolumna jest poprawna
				return 1;
			}
		}

		sudoku->plansza[rzad][kolumna] = 0; // jesli dane wypelnienie nie pozwoli rozwiazac sudoku to cofamy ten ruch
	}

	return 0;
}
