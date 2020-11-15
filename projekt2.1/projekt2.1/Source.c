#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <cctype>
#define _CRT_SECURE_NO_WARNINGS

struct obraz
{
	int szerokosc; //8
	int wysokosc; //8// wymiary na pocz¹tek
	int max_szarosc; // jedna wartosc do ktorej porownojemy
	int** macierz; // tyle ,,pikseli''

	int zaladowany; //pole do oznaczania czy obraz jest zaladowany - 1 jesli to prawda
};

struct baza
{
	int rozmiar;
	struct obraz* obrazy;
};

struct obraz* dodaj_obraz(struct baza* baza) // obrazy[]
{
	if (baza->rozmiar == 0)
	{
		baza->obrazy = (struct obraz*)malloc(sizeof(struct obraz));
		baza->rozmiar = 1;

		return &baza->obrazy[baza->rozmiar - 1];
	}
	
	baza->rozmiar++;
	
	struct obraz* nowe = (struct obraz*)realloc(baza->obrazy,baza->rozmiar * sizeof(struct obraz)); // realloc psuje poprzednie struktury?
	if (nowe == NULL)
	{
		exit(3);
	}
	baza->obrazy = nowe;
	
	return &baza->obrazy[baza->rozmiar - 1];
}

void nowy_obraz(struct obraz* obraz)
{
	obraz->macierz = (int**)calloc(obraz->szerokosc, sizeof(int*));
	if (obraz->macierz == NULL)
	{
		exit(3);
	}

	for (int i = 0; i < obraz->szerokosc; i++)
	{
		obraz->macierz[i] = (int*)calloc(obraz->wysokosc, sizeof(int));

		if (obraz->macierz[i] == NULL)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				free(obraz->macierz[j]);
			}

			free(obraz->macierz);
			exit(3);
		}
	}

	obraz->zaladowany = 1;
}

void wypisz_obraz(struct obraz* obraz)
{
	printf("szerokosc: %d, wysokosc: %d, max szarosc: %d\n", obraz->szerokosc, obraz->wysokosc, obraz->max_szarosc);

	for (int i = 0; i < obraz->szerokosc; i++)
	{
		for (int j = 0; j < obraz->wysokosc; j++)
		{
			printf("%d ", obraz->macierz[i][j]);
		}
		printf("\n");
	}
}

void odczyt_pliku(struct baza* baza)
{
	char bufor[50] = {0};

	printf("Podaj nazwe pliku z rozszerzeniem PMG:\n");
	scanf("%s", &bufor);

	FILE* plik = fopen(bufor, "r");
	if (plik == 0)
	{
		exit(1);
	}

	struct obraz* obraz = dodaj_obraz(baza);

	fscanf(plik, "%s", &bufor);

	if (strcmp(bufor, "P2") != 0)
	{
		exit(2);
	}

	while (1)
	{
		int odczytane = fscanf(plik, "%d %d", &obraz->szerokosc, &obraz->wysokosc);

		if (odczytane == 0)
		{
			fscanf(plik, "%s", &bufor);
		}
		else if (odczytane == 2)
		{
			break;
		}
	}

	while (1)
	{
		int odczytane = fscanf(plik, "%d", &obraz->max_szarosc);

		if (odczytane == 0)
		{
			fscanf(plik, "%s", &bufor);
		}
		else if (odczytane == 1)
		{
			break;
		}
	}

	nowy_obraz(obraz);

	for (int i = 0; i < obraz->szerokosc; i++)
	{
		for (int j = 0; j < obraz->wysokosc; j++)
		{
			while (1)
			{
				int odczytane = fscanf(plik, "%d", &obraz->macierz[i][j]);

				if (odczytane == 0)
				{
					fscanf(plik, "%s", &bufor);
				}
				else if (odczytane == 1)
				{
					break;
				}
			}
		}
	}

	fclose(plik);
}

void zapis_do_pliku(struct obraz* obraz)
{
	if (obraz->zaladowany != 1) // pole do sprawdzania czy istnieje obraz
	{
		exit(1);
	}

	char bufor[50] = {0};
	printf("Podaj nazwe pliku ktory ma powstac\n");
	scanf("%s", &bufor);

	FILE* plik;

	plik = fopen(bufor, "w"); //miejsce docelowe pliku w nawiasie // jesli sie nie otworzy zwraca null
	if (bufor == 0) // sprawdzamy dla dla pliku, a nie dla nazwa
	{
		exit(1); // bo exit zwraca wartosc
	}

	fprintf(plik, "P2\n");
	fprintf(plik, "%d %d\n", obraz->szerokosc, obraz->wysokosc);
	fprintf(plik, "%d\n", obraz->max_szarosc);


	for (int i = 0; i < obraz->szerokosc; i++)
	{
		for (int j = 0; j < obraz->wysokosc; j++)
		{
			fprintf(plik, "%d ", obraz->macierz[i][j]);
		}

		fprintf(plik, "\n");
	}

	fclose(plik);
}

void wypisz_baze(struct baza* baza)
{
	for (int i = 0; i < baza->rozmiar; i++)
	{
		printf("Obraz %d\n", i + 1);
		
		wypisz_obraz(&baza->obrazy[i]);
	}
}

void menu()
{
	char napis[50] = {0};
	struct baza baza = {0};

	while (1)
	{
		wypisz_baze(&baza);
		
		printf("Menu:\n1Odczyt pliku\n2....\n3Zapis do pliku\n4.Zamknij\n");
		scanf("%s", napis);

		int wybor = atoi(napis); //ascii na inta

		switch (wybor)
		{
		case 0: // wynik funkcji atoi jesli nie mozna zamienic napisu na int jest rowny 0
			printf("Wprowadziles napis zamiast liczby, sprobuj ponownie\n");
			break;

		case 1:
			odczyt_pliku(&baza);
			break;

		case 2:
			//();
			break;

		case 3:
			zapis_do_pliku(NULL);
			break;

		case 4:
			return;

		default: // uzytkownik wprowadzil liczbe ale nie ma takiej opcji
			printf("Niepoprawny wybor, sprobuj ponownie\n");
			break;
		}
	}
}

int main()
{
	menu();

	return 0;
}
