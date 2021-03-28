#ifndef SUDOKU_H
#define SUDOKU_H

struct sudoku {
	int** plansza;
};

typedef struct sudoku* sudoku_ptr;

sudoku_ptr sudoku_nowe();
void sudoku_zwolnij(sudoku_ptr);
void sudoku_wypisz(sudoku_ptr);

int sudoku_solver(sudoku_ptr, int, int);
int sudoku_mozna_ruch(sudoku_ptr, int, int, int);

#endif // !SUDOKU_H