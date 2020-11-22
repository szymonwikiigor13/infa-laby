#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

	struct obraz* nowe = (struct obraz*)realloc(baza->obrazy, baza->rozmiar * sizeof(struct obraz)); // realloc psuje poprzednie struktury?
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
	char bufor[50] = { 0 };

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

void zapis_do_pliku(struct baza* baza, int index)
{
	struct obraz* obraz = &baza->obrazy[index];
	
	if (obraz->zaladowany != 1) // pole do sprawdzania czy istnieje obraz
	{
		exit(1);
	}

	char bufor[50] = { 0 };
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
		printf("Obraz id: %d\n", i);

		wypisz_obraz(&baza->obrazy[i]);
	}
}

void usun_obraz(struct baza* baza, int index)
{
	if (baza->rozmiar == 0)
	{
		exit(4);
	}

	for (int i = index; i < baza->rozmiar - 1; i++)
	{
		baza->obrazy[i] = baza->obrazy[i + 1];
	}

	baza->rozmiar--;

	struct obraz* nowe = (struct obraz*)realloc(baza->obrazy, baza->rozmiar * sizeof(struct obraz));
	if (nowe == NULL)
	{
		exit(4);
	}
	baza->obrazy = nowe;
}

// Przetwarzanie obrazów

void obrot90kstopni(struct baza* baza, int index, int k)
{
	if (k <= 0 || k % 4 == 0) return;

	struct obraz* obraz = &baza->obrazy[index];

	struct obraz* nowy = (struct obraz*)malloc(sizeof(struct obraz));
	if (nowy == NULL)
	{
		exit(4);
	}

	nowy->max_szarosc = obraz->max_szarosc;

	if (k % 2 == 0)
	{
		nowy->szerokosc = obraz->szerokosc;
		nowy->wysokosc = obraz->wysokosc;

		nowy_obraz(nowy);

		for (int i = 0; i < nowy->szerokosc; i++)
		{
			int pixel = nowy->wysokosc - 1;

			for (int j = 0; j < nowy->wysokosc; j++)
			{
				nowy->macierz[i][j] = obraz->macierz[i][pixel--];
			}
		}
	}
	else
	{
		nowy->szerokosc = obraz->wysokosc;
		nowy->wysokosc = obraz->szerokosc;

		int wiersz = 0, kolumna = 0;

		if (k % 4 == 1)
		{
			for (int i = 0; i < obraz->szerokosc; i++)
			{
				for (int j = obraz->wysokosc - 1; j >= 0; j--)
				{
					nowy->macierz[wiersz][kolumna] = obraz->macierz[i][j];
					kolumna++;
				}
				wiersz++;
				kolumna = 0;
			}
		}
		else
		{

		}
	}

	free(obraz);
	baza->obrazy[index] = *nowy;
}

void zapis_do_pliku_csv(int* wyniki, int rozmiar) {
	FILE* wypistablicy;
	char nazwa[50] = { 0 };
	printf("Podaj nazwe pliku csv do ktorego zapisany zostanie histogram:\n");
	scanf("%s", nazwa);

	wypistablicy = fopen(nazwa, "w");  //miejsce docelowe pliku w nawiasie // jesli sie nie otworzy zwraca null
	if (wypistablicy == 0) // sprawdzamy dla dla pliku, a nie dla nazwa
	{
		abort();// bo exit zwraca wartosc
	}
	//zabez
	for (int i = 0; i < rozmiar; i++) {
		fprintf(wypistablicy, "%d\n", wyniki[i]);
	}

	fclose(wypistablicy);
}

void histogram(struct baza* baza, int index)
{
	struct obraz* obraz = &baza->obrazy[index];

	int* histogram = (int*)calloc(obraz->max_szarosc + 1, sizeof(int));

	for (int i = 0; i < obraz->szerokosc; i++)
	{
		for (int j = 0; j < obraz->wysokosc; j++)
		{
			histogram[obraz->macierz[i][j]]++;
		}
	}

	zapis_do_pliku_csv(histogram, obraz->max_szarosc + 1);
}

void negatyw(struct baza* baza, int index)
{
	struct obraz* obraz = &baza->obrazy[index];

	for (int i = 0; i < obraz->szerokosc; i++)
	{
		for (int j = 0; j < obraz->wysokosc; j++)
		{
			obraz->macierz[i][j] = obraz->max_szarosc - obraz->macierz[i][j];
		}
	}
}

void sol_i_pieprz(struct baza* baza, int index)
{
	struct obraz* obraz = &baza->obrazy[index];

	for (int i = 0; i < obraz->szerokosc; i++)
	{
		for (int j = 0; j < obraz->wysokosc; j++)
		{
			if (rand() % 10 == 0)
			{
				obraz->macierz[i][j] = (rand() % 2 == 0) ? obraz->max_szarosc : 0; // przypisanie warunkowe = (warunek) ? <wartoœæ jeœli prawda> : <wartoœæ jeœli fa³sz>
			}
		}
	}
}

void gauss(struct baza* baza, int index)
{
	struct obraz* obraz = &baza->obrazy[index];

	struct obraz* nowy = (struct obraz*)malloc(sizeof(struct obraz));
	if (nowy == NULL)
	{
		exit(5);
	}

	nowy->szerokosc = obraz->szerokosc;
	nowy->wysokosc = obraz->wysokosc;
	nowy->max_szarosc = obraz->max_szarosc;

	nowy_obraz(nowy);

	for (int i = 1; i < obraz->szerokosc - 1; i++) // zawê¿one okno
	{
		for (int j = 1; j < obraz->wysokosc - 1; j++)
		{
			int gora_l = obraz->macierz[i - 1][j - 1];
			int gora_p = obraz->macierz[i + 1][j - 1];
			int gora = obraz->macierz[i][j - 1] * 2;

			int dol_l = obraz->macierz[i - 1][j + 1];
			int dol_p = obraz->macierz[i + 1][j + 1];
			int dol = obraz->macierz[i][j + 1] * 2;

			int lewo = obraz->macierz[i - 1][j] * 2;
			int prawo = obraz->macierz[i + 1][j] * 2;
			int srodek = obraz->macierz[i][j] * 4;

			nowy->macierz[i][j] = (srodek + gora + dol + lewo + prawo + gora_l + gora_p + dol_l + dol_p) / 16;
		}
	}

	for (int i = 0; i < obraz->szerokosc; i++)
	{
		if (i == 0 || i == obraz->szerokosc - 1) {

			for (int j = 0; j < obraz->wysokosc; j++)
			{
				nowy->macierz[i][j] = obraz->macierz[i][j];
			}
			
		}
	}

	for (int j = 0; j < obraz->wysokosc; j++)
	{
		if (j == 0 || j == obraz->wysokosc - 1) {
			for (int i = 0; i < obraz->szerokosc; i++)
			{
				nowy->macierz[i][j] = obraz->macierz[i][j];
			}
		}
	}

	for (int i = 0; i < obraz->szerokosc; i++)
	{
		for (int j = 0; j < obraz->wysokosc; j++)
		{
			obraz->macierz[i][j] = nowy->macierz[i][j];
		}
	}

	free(nowy);
}

//

int main()
{
	char napis[50] = { 0 };
	struct baza baza = { 0 };
	int index = -1;

	srand(time(NULL));

	while (1)
	{
		printf("Menu:\n1. Dodawanie pliku\n2. Wybierz aktywny obraz\n3. Zapisz do pliku\n4. Usun aktywny obraz\n5. Wypisz baze obrazow\n6. Przetwarzanie aktywnego obrazu\n7. Zamknij\n");

		if (index < 0)
		{
			printf("Brak aktywnego obrazu.\n");
		}
		else
		{
			printf("Aktywny obraz: id %d\n", index);
		}

		scanf("%s", napis);

		int wybor = atoi(napis); //ascii na inta

		switch (wybor)
		{
		case 0: // wynik funkcji atoi jesli nie mozna zamienic napisu na int jest rowny 0
			printf("Wprowadziles napis zamiast liczby, sprobuj ponownie\n");
			break;

		case 1:
			odczyt_pliku(&baza);
			printf("Pomyslnie odczytano obraz.\n");
			break;

		case 2:
			if (baza.rozmiar < 1)
			{
				printf("Zbyt malo obrazow\n");
				break;
			}

			printf("Podaj numer obrazu <0; %d>\n", baza.rozmiar - 1);
			scanf("%s", napis);

			int wybor2 = atoi(napis);

			if (wybor2 < 0 || wybor2 >= baza.rozmiar)
			{
				printf("Niepoprawny wybor, maksymalny id w bazie to %d\n", baza.rozmiar - 1);
				break;
			}

			index = wybor2;
			printf("Wybrany obraz to: \n");
			wypisz_obraz(&baza.obrazy[index]);
			break;

		case 3:
			printf("Zapis do pliku aktualnie wybranego obrazu...\n");
			zapis_do_pliku(&baza, index);
			break;

		case 4:
			printf("Usuwanie aktualnie wybranego obrazu...\n");
			usun_obraz(&baza, index);

			index = -1;
			break;

		case 5:
			wypisz_baze(&baza);
			break;

		case 6:
			if (index < 0)
			{
				printf("Brak aktywnego obrazu.\n");
			}
			else
			{
				printf("Aktywny obraz: id %d\n", index);
				wypisz_obraz(&baza.obrazy[index]);
			}

			printf("Opcje przetwarzania:\n1. Obroc obraz o k*90 stopni\n2. Histogram\n3. Negatyw\n4. Sol i pieprz\n5. Filtr Gaussa\n6. Anuluj\n");
			scanf("%s", napis);


			int wybor3 = atoi(napis);

			switch (wybor3)
			{
			case 0: // wynik funkcji atoi jesli nie mozna zamienic napisu na int jest rowny 0
				printf("Wprowadziles napis zamiast liczby, sprobuj ponownie\n");
				break;

			case 1:
				obrot90kstopni(&baza, index, 1); // wczytywanie k
				wypisz_obraz(&baza.obrazy[index]);
				break;

			case 2:
				histogram(&baza, index);
				break;

			case 3:
				negatyw(&baza, index);
				break;

			case 4:
				sol_i_pieprz(&baza, index);
				break;

			case 5:
				gauss(&baza, index);
				break;

			case 6:
				break;

			default:
				printf("Niepoprawny wybor, anulowano przetwarzanie\n");
				break;
			}

			break;

		case 7:
			return 0;

		default: // uzytkownik wprowadzil liczbe ale nie ma takiej opcji
			printf("Niepoprawny wybor, sprobuj ponownie\n");
			break;
		}
	}
}
