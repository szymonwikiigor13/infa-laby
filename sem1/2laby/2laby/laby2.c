
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS

//(ax + b) / (cx + d)
void dziedzina(float* min, float* max)
{
	*min = 1;
	*max = 0;

	while (*max < *min)
	{
		printf("Podaj dolna granice dziedziny: ");  //prosimy o podanie granic funkcji
		scanf("%f", min);
		printf("Podaj gorna granice dziedziny: ");
		scanf("%f", max);

		if (*max <= *min)
		{
			printf("Podaj prawidlowa dziedzine\n");
		}
		//zabez
	}

}

void parametry(float* wspolczynnik)
{


		printf("Mamy funkcje okreslona wzorem (ax + b) / (cx + d) gdzie x to zmienna, podaj odpowiednie parametry\n");
		float a, b, c, d;
		//problem z atof
		
		printf("Podaj parametr a: \n");
		scanf("%f", &a);  //pobranie parametrow od uzytkownika
		
		printf("Podaj parametr b: \n");
		scanf("%f", &b);
		
		
		printf("Podaj parametr c: \n");
		scanf("%f", &c);
		
		
		printf("Podaj parametr d: \n");
		scanf("%f", &d);     
		
		//zapisywanie parametrów w tablicy jako współczynniki
		
		if (a == 0 && b == 0 && c == 0 && d == 0)
		{
			printf("Ta funkcja jest nieoznaczona, podaj inne parametry: \n");
			printf("Podaj parametr a: \n");
			scanf("%f", &a);
			printf("Podaj parametr b: \n");
			scanf("%f", &b);
			printf("Podaj parametr c: \n");
			scanf("%f", &c);
			printf("Podaj parametr d: \n");
			scanf("%f", &d);
		}
		//zabez
		if ((c == 0) && (d == 0) && (a != 0 || b != 0))
		{
			printf("Ta funkcja dazy do nieskonczonosci, podaj inne parametry (szczegolnie c i d):\n");
			printf("Podaj parametr a: \n");
			scanf("%f", &a);
			printf("Podaj parametr b: \n");
			scanf("%f", &b);
			printf("Podaj parametr c: \n");
			scanf("%f", &c);
			printf("Podaj parametr d: \n");
			scanf("%f", &d);
		}
		//zabez
		wspolczynnik[0] = a;
		wspolczynnik[1] = b;
		wspolczynnik[2] = c;
		wspolczynnik[3] = d;
	
}

int rozmiar_tablicy(float min, float max, float czestotliwosc)
{

	//czas próbkowania to 0.004 w moim przypadku 
	return ceil((max - min) * czestotliwosc);
}

float* generator(float* wspolczynniki, float min, float max, int rozmiar, float czas_probkowania)
{
	//(ax + b) / (cx + d)
	float* wyniki = (float*)calloc(rozmiar, sizeof(float));
	float x = min;
	if (wyniki == 0)
	{
		exit(1);
	}
	//zabez
	for (int i = 0; i < rozmiar; i++)
	{
		if ((wspolczynniki[2] * x + wspolczynniki[3]) == 0)
		{
			x += czas_probkowania;
		}
		//zabez
		wyniki[i] = (wspolczynniki[0] * x + wspolczynniki[1]) / (wspolczynniki[2] * x + wspolczynniki[3]);
		x += czas_probkowania;
	}

	return wyniki;
}


void zapis_do_pliku_csv(char* nazwa, float* wyniki, int rozmiar) {
	FILE* wypistablicy;

	wypistablicy = fopen(nazwa, "w");  //miejsce docelowe pliku w nawiasie // jesli sie nie otworzy zwraca null
	if (wypistablicy == 0) // sprawdzamy dla dla pliku, a nie dla nazwa
	{
		abort();// bo exit zwraca wartosc
	}
	//zabez
	for (int i = 0; i < rozmiar; i++) {
		fprintf(wypistablicy, "%f\n", wyniki[i]);
	}

	fclose(wypistablicy);
}

void odczyt_z_csv(char* nazwa, int* rozmiar) // int bo zwracamy odczytany rozmiar
{
	FILE* plik;
	*rozmiar = 0;
	plik = fopen(nazwa, "r");
	if (plik == 0) // sprawdzamy dla dla plik, a nie dla nazwa
	{
		printf("Blad z plikiem ");
		return;// zatrzymanie z return bo funkcja float
	}

	//// zabez
	//float* wynik = (float*)calloc(1, sizeof(float)); // calloc zeruje,a malloc nie 
	//if (wynik == 0)
	//{
	//	exit(1);
	//}

	int linia = 1;
	while (!feof(plik))
	{
		float temp = 0.0;

		fscanf(plik, "%f\n", &temp);

		printf("%d. %f\n", linia++, temp);


		//wynik[*rozmiar] = temp; //blad ze scanf (zwraca -1)

		//(*rozmiar)++;

		//float* realoc = (float*) realloc(wynik, sizeof(wynik) + sizeof(float)); //powiekszanie wyniku o nowa wartosc
		//if (realoc == 0)
		//{
		//	exit(1);
		//}
		//
		//wynik = realoc;
	}

	*rozmiar = linia - 1;

	fclose(plik);
}

float* szum(int rozmiar) {
	srand(time(NULL));

	float* sz = (float*)calloc(rozmiar, sizeof(float));
	if (sz == 0)
	{
		exit(1);
	}
	//zabez
	for (int i = 0; i < rozmiar; i++)
	{
		if (rand() % 5 == 0) // 20% szans na szum
		{
			float x = ((float)rand() / (float)(RAND_MAX)) * 0.1; // (0; 0,1>     

			if (rand() % 2 == 0) // 50% szans na szum dodatni
			{
				sz[i] = x;

			}
			else
			{
				sz[i] = -x;
			}
		}
		else // brak szumu
		{
			sz[i] = 0;
		}
	}

	return sz;
}

void szum_do_wynikow(float* wyniki, float* szum, int rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
	{
		wyniki[i] += szum[i];
	}
}

int komparator_rosnacy(const void* a, const void* b)
{
	float arg1 = *((float*)a); // rzutujemy argumenty komparatora na właściwy typ z tablicy
	float arg2 = *((float*)b);

	if (arg1 < arg2) {
		return -1;
	}
	if (arg1 > arg2) {
		return 1;
	}

	return 0;
}
// potrzebne do qsort

float* odszumiony_sygnal(float* wyniki, int rozmiar)
{
	if (rozmiar == 0)
	{
		abort();
	}

	float* mediany = (float*)calloc(rozmiar, sizeof(float)); // funkcja zwraca void*, my chcemy tablice floatów
	int index = 0;

	float temp[5];

	temp[0] = wyniki[0];
	temp[1] = wyniki[0];
	temp[2] = wyniki[0];
	temp[3] = wyniki[1];
	temp[4] = wyniki[2];

	qsort(temp, 5, sizeof(float), komparator_rosnacy);
	mediany[index++] = temp[2];

	temp[0] = wyniki[0];
	temp[1] = wyniki[0];
	temp[2] = wyniki[1];
	temp[3] = wyniki[2];
	temp[4] = wyniki[3];

	qsort(temp, 5, sizeof(float), komparator_rosnacy);
	mediany[index++] = temp[2];

	for (int i = 0; i < (rozmiar - 4); i++)
	{
		temp[0] = wyniki[i];
		temp[1] = wyniki[i + 1];
		temp[2] = wyniki[i + 2];
		temp[3] = wyniki[i + 3];
		temp[4] = wyniki[i + 4];

		qsort(temp, 5, sizeof(float), komparator_rosnacy);
		mediany[index++] = temp[2];
	}

	temp[0] = wyniki[rozmiar - 4];
	temp[1] = wyniki[rozmiar - 3];
	temp[2] = wyniki[rozmiar - 2];
	temp[3] = wyniki[rozmiar - 1];
	temp[4] = wyniki[rozmiar - 1];

	qsort(temp, 5, sizeof(float), komparator_rosnacy);
	mediany[index++] = temp[2];

	temp[0] = wyniki[rozmiar - 3];
	temp[1] = wyniki[rozmiar - 2];
	temp[2] = wyniki[rozmiar - 1];
	temp[3] = wyniki[rozmiar - 1];
	temp[4] = wyniki[rozmiar - 1];

	qsort(temp, 5, sizeof(float), komparator_rosnacy);
	mediany[index++] = temp[2];

	return mediany;
}

void dzialanie_bez_zapisu()
{
	float wspolczynnik[4];
	parametry(wspolczynnik);

	float min;
	float max;

	dziedzina(&min, &max);

	float czestotliwosc = 1 / 0.004f;// bez f nie dziala idk
	float czas_probkowania = 0.004f;

	int rozmiar = rozmiar_tablicy(min, max, czestotliwosc);

	float* wyniki = generator(wspolczynnik, min, max, rozmiar, czas_probkowania);
	float* sz = szum(rozmiar);


	szum_do_wynikow(wyniki, sz, rozmiar);
	printf("Zaszumiony sygnal\n");
	for (int i = 0; i < rozmiar; i++) {
		
		printf("%d. %f\n", i + 1, wyniki[i]);
	}

	float* odsz = odszumiony_sygnal(wyniki, rozmiar);
	printf("Odszumiony sygnal\n");
	for (int i = 0; i < rozmiar; i++) {
		
		printf("%d. %f\n", i + 1, odsz[i]);
	}

	free(wyniki);
	free(sz);
	free(odsz);
}

void dzialanie()
{
	float wspolczynnik[4];
	parametry(wspolczynnik);

	float min;
	float max;

	dziedzina(&min, &max);

	float czestotliwosc = 1 / 0.004f;
	float czas_probkowania = 0.004f;

	int rozmiar = rozmiar_tablicy(min, max, czestotliwosc);

	float* wyniki = generator(wspolczynnik, min, max, rozmiar, czas_probkowania);
	float* sz = szum(rozmiar);

	szum_do_wynikow(wyniki, sz, rozmiar);
	float* odsz = odszumiony_sygnal(wyniki, rozmiar);

	zapis_do_pliku_csv("wyniki.csv", odsz, rozmiar);

	free(wyniki);
	free(sz);
	free(odsz);
}

void wczytaj()
{
	int rozmiar = 0;
	odczyt_z_csv("wyniki.csv", &rozmiar);

	printf("Plik zawiera %d liczb\n", rozmiar);
}


void menu()
{
	char napis[50] = { 0 };

	while (1) {
		printf("Menu:\n1.Nowy\n2.Odczyt z pliku\n3.Nowy z zapisem do pliku\n4.Zamknij\n");
		scanf("%s", napis);

		int wybor = atoi(napis); //ascii na inta

		switch (wybor) {
		case 0: // wynik funkcji atoi jesli nie mozna zamienic napisu na int jest rowny 0
			printf("Wprowadziles napis zamiast liczby, sprobuj ponownie\n");
			break;

		case 1:
			dzialanie_bez_zapisu();
			break;

		case 2:
			wczytaj();
			break;

		case 3:
			dzialanie();
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
