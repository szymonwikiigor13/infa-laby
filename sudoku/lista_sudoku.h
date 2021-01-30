#ifndef LISTA_SUDOKU_H
#define LISTA_SUDOKU_H

#include "sudoku.h"

struct lista_sudoku {
	sudoku_ptr sudoku;

	struct lista_sudoku* poprzedni;
	struct lista_sudoku* nastepny;
};

typedef struct lista_sudoku* lista_sudoku_ptr;

lista_sudoku_ptr lista_sudoku_nowa();
void lista_sudoku_zwolnij(lista_sudoku_ptr);
void lista_sudoku_dodaj(lista_sudoku_ptr, sudoku_ptr);
void lista_sudoku_wypisz(lista_sudoku_ptr);

void wczytaj_sudoku_z_pliku(lista_sudoku_ptr, char*);
int lista_sudoku_rozmiar(lista_sudoku_ptr);

#endif // !LISTA_SUDOKU_H