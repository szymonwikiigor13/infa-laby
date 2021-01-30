#define _CRT_SECURE_NO_WARNINGS

#include "sudoku.h"
#include "lista_sudoku.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dzialanie(sudoku_ptr sudoku) {
	if (sudoku == NULL) {
		printf("Nie masz aktywnego sudoku!\n");
		return;
	}

	while (1) {
		char bufor[10] = { 0 };
		printf("Podaj koordynaty komorki lub 'return' aby wrocic do menu:\n");

		printf("Numer rzedu:\n");
		scanf("%s", bufor);

		if (strcmp(bufor, "return") == 0) {
			return;
		}

		int rzad = atoi(bufor);

		if (rzad < 1 || rzad > 9) {
			printf("Niepoprawna wartosc!\n");
			return;
		}

		printf("Numer kolumny:\n");
		scanf("%s", bufor);

		if (strcmp(bufor, "return") == 0) {
			return;
		}

		int kolumna = atoi(bufor);

		if (kolumna < 1 || kolumna > 9) {
			printf("Niepoprawna wartosc!\n");
			return;
		}

		printf("Podaj liczbe do wprowadzenia:\n");
		scanf("%s", bufor);

		if (strcmp(bufor, "return") == 0) {
			return;
		}

		int wartosc = atoi(bufor);

		if (wartosc < 1 || wartosc > 9) {
			printf("Niepoprawna wartosc!\n");
			return;
		}

		int ostatni = sudoku->plansza[rzad - 1][kolumna - 1];
		sudoku->plansza[rzad - 1][kolumna - 1] = wartosc;

		if (sudoku_mozna_ruch(sudoku, rzad, kolumna, wartosc) == 0) {
			printf("Niepoprawny ruch.\nPrzywracam ostatni stan gry.\n");
			sudoku->plansza[rzad - 1][kolumna - 1] = ostatni;
		}

		sudoku_wypisz(sudoku);
	}
}

int main() {
	lista_sudoku_ptr lista = lista_sudoku_nowa();

	char wejscie[99] = { 0 };
	sudoku_ptr wybrany = NULL;

	while (1) {
		printf("Menu\n");
		scanf("%99s", wejscie);

		if (strcmp(wejscie, "exit") == 0) {
			printf("Zamykam program.\n");
			break;
		}

		int wybor = atoi(wejscie);

		switch (wybor)
		{
		case 0:
			printf("Wprowadziles napis zamiast liczby, sprobuj ponownie.\n");
			break;

		case 1:
			lista_sudoku_wypisz(lista);
			break;

		case 2:
			printf("Podaj numer sudoku:\n");
			scanf("%99s", wejscie);

			int numer = atoi(wejscie);
			if (numer <= 0 || numer > lista_sudoku_rozmiar(lista)) {
				printf("Niepoprawny wybór, sprobuj ponownie.\n");
			}
			else {
				wybrany = lista_sudoku_indeks(lista, numer);

				printf("Wybrane sudoku:\n");
				sudoku_wypisz(wybrany);
			}
			break;

		case 3:
			printf("Podaj nazwe pliku z sudoku:\n");
			scanf("%99s", wejscie);

			wczytaj_sudoku_z_pliku(lista, wejscie);
			break;

		case 4:
			dzialanie(wybrany);
			break;

		case 5:
			if (wybrany == NULL) {
				printf("Nie masz aktywnego sudoku!\n");
				break;
			}

			if (sudoku_solver(wybrany, 0, 0) == 1) {
				sudoku_wypisz(wybrany);
			}
			else {
				printf("Wybrane sudoku nie ma rozwiazania.\n");
			}

			break;

		default:
			printf("Niepoprawny wybor, sprobuj ponownie\n");
			break;
		}
	}

	lista_sudoku_zwolnij(lista);
}