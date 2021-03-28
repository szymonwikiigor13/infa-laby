#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <locale.h>


typedef struct
{
	char imie[30], nazwisko[30], grupa[30], numer[20];
	struct Kontakt* poprzedni;
	struct Kontakt* nastepny; // pomaga w umieszczeniu kontaktu w odpowiednim miejscu
} Kontakt;

Kontakt* ostatni_kontakt(Kontakt* glowny)
{
	Kontakt* tmp = glowny;

	while (tmp->nastepny != NULL) {
		tmp = tmp->nastepny;
	}

	return tmp;
}

Kontakt* wczytaj_z_pliku(Kontakt* glowny)
{
	char nazwa[100];
	FILE* plik = NULL;
	Kontakt* nowy, * koniec;

	while (plik == NULL)
	{
		printf("\nPodaj lokalizacje pliku: ");
		scanf("%99s", nazwa);
		plik = fopen(nazwa, "r");

		if (plik == NULL) {
			printf("Nie znaleziono pliku\n");
		}
	}

	if (glowny != NULL) { //jesli juz wczesniej byly kontakty
		koniec = ostatni_kontakt(glowny);
	}
	else {
		koniec = NULL;
	}

	while (!feof(plik)) //dopoki nie mamy konca pliku
	{
		nowy = malloc(sizeof(Kontakt));
		fscanf(plik, "%[^;] ; %[^;] ; %[^;] ; %s\n", nowy->imie, nowy->nazwisko, nowy->numer, nowy->grupa);

		if (glowny == NULL) //jesli nie ma jeszcze zadnych kontaktow
		{
			glowny = nowy;
			nowy->nastepny = NULL;
			nowy->poprzedni = NULL;
			koniec = nowy;
		}
		else
		{
			nowy->poprzedni = koniec;
			koniec->nastepny = nowy;
			nowy->nastepny = NULL;
			koniec = nowy;
		}
	}

	fclose(plik);
	return glowny;
}

Kontakt* dodaj_kontakt(char imie[30], char nazwisko[30], char grupa[30], char numer[10], Kontakt* poprzedni, Kontakt* glowny)
{
	Kontakt* nowy, * tmp;

	nowy = malloc(sizeof(Kontakt));
	strcpy(nowy->imie, imie); //strcpy -> string copy
	strcpy(nowy->nazwisko, nazwisko);
	strcpy(nowy->grupa, grupa);
	strcpy(nowy->numer, numer);
	nowy->poprzedni = poprzedni;

	if (poprzedni == NULL)
	{
		nowy->nastepny = glowny;
	}
	else
	{
		nowy->nastepny = poprzedni->nastepny;
		poprzedni->nastepny = nowy;
	}

	tmp = nowy->nastepny;

	if (tmp != NULL) {
		tmp->poprzedni = nowy;
	}

	if (poprzedni == NULL) {
		glowny = nowy;
	}

	return glowny;
}

Kontakt* usun(Kontakt* poprzedni, Kontakt* glowny)
{
	Kontakt* tmp;

	if (poprzedni == NULL) { //jesli nie ma poprzedniego
		return glowny;
	}

	if (poprzedni->poprzedni != NULL) //jesli poprzedni ma przodkow
	{
		tmp = poprzedni->poprzedni;
		tmp->nastepny = poprzedni->nastepny;
	}

	if (poprzedni->nastepny != NULL) //jesli poprzedni ma nastepcow
	{
		tmp = poprzedni->nastepny;
		tmp->poprzedni = poprzedni->poprzedni;
	}

	if (poprzedni->poprzedni == NULL) { //jesli poprzedni jest pierwszym kontaktem
		glowny = poprzedni->nastepny;
	}

	free(poprzedni);
	return glowny;
}

Kontakt* szukaj_lub_usun(int akcja, Kontakt* glowny) //akcja=1 usuwaj, wpp. wyszukaj tylko
{
	char fraza[100];
	Kontakt* tmp, * tmp1;

	tmp = glowny;

	if (akcja == 1) {
		printf("Usun WSZYSTKIE kontakty z podanym ciagiem znakow (imie, nazwisko lub grupa)\n");
	}

	printf("Podaj fraze do wyszukania:\n");
	scanf("%99s", fraza);

	printf("Znaleziono:\nimie; nazwisko; grupa; numer\n");

	while (tmp != NULL)
	{
		if (strstr(tmp->nazwisko, fraza) != NULL |
			strstr(tmp->imie, fraza) != NULL |
			strstr(tmp->grupa, fraza) != NULL) // strstr(napis, podnapis) -> wyszukiwanie podnapisu w napisie
		{
			printf("%s; %s; %s; %s\n", tmp->imie, tmp->nazwisko, tmp->grupa, tmp->numer);

			if (akcja == 1) //usuwanie wpisu
			{
				tmp1 = tmp->poprzedni;
				glowny = usun(tmp, glowny);

				if (tmp1 == NULL) {
					tmp = glowny;
				}
				else {
					tmp = tmp1;
				}
			}
		}
		tmp = tmp->nastepny;
	}

	return glowny;
}

Kontakt* sortuj_kontakty(int sort, Kontakt* glowny) // 0 brak; 1 imie; 2 nazwisko; else grupa
{
	Kontakt* tmp, * pierwszyNowy, * min, * ostatniNowy, * tmp1;

	pierwszyNowy = glowny;
	ostatniNowy = glowny;

	int start = 1, porownanie;

	if (sort == 0) { // nie sortujemy
		return glowny;
	}

	while (glowny != NULL)
	{
		tmp = glowny;
		min = glowny;

		while (tmp != NULL)
		{
			switch (sort)
			{
			case 1: //sortuj alfabetycznie przez imie
				porownanie = strcoll(min->imie, tmp->imie); //strcoll -> porownywanie napisow z uwzglednieniem lokalizacji (polskie znaki)
				break;
			case 2: //sortuj alfabetycznie przez nazwisko
				porownanie = strcoll(min->nazwisko, tmp->nazwisko);
				break;
			default: //sortuj alfabetycznie przez grupe
				porownanie = strcoll(min->grupa, tmp->grupa);
				break;
			}

			if (porownanie == 1) { //jesli napis w min jest pozniej w alfabecie ni¿ tmp
				min = tmp;
			}

			tmp = tmp->nastepny;
		}

		tmp1 = min->poprzedni; //pierwszy wynik
		
		if (tmp1 != NULL) {
			tmp1->nastepny = min->nastepny;
		}
		else {
			glowny = min->nastepny;
		}

		tmp1 = min->nastepny;

		if (tmp1 != NULL) {
			tmp1->poprzedni = min->poprzedni;
		}

		if (start == 1) //jesli to jest pierwsze przejscie petli
		{
			start = 0;
			pierwszyNowy = min;
			ostatniNowy = min;
			min->poprzedni = NULL;
		}
		else
		{
			ostatniNowy->nastepny = min;
			min->poprzedni = ostatniNowy;
			min->nastepny = NULL;
			ostatniNowy = min;
		}
	}
	return pierwszyNowy;
}

Kontakt* nowy_kontakt(int sort, Kontakt* glowny) //funkcja wczytuje dane z klawiatury i wywoduje dodaj_kontakt
{ // sort -> 0 na koniec; 1 wg imienia; 2 wg nazwiska; else wg grupy
	Kontakt* tmp;

	int koniec = 0, porownanie;
	char imie[30], nazwisko[30], grupa[30], numer[10];

	printf("\nPodaj imie: ");
	scanf("%99s", imie);
	printf("\nPodaj nazwisko: ");
	scanf("%99s", nazwisko);
	printf("\nPodaj grupa: ");
	scanf("%99s", grupa);
	printf("\nPodaj numer: ");
	scanf("%99s", numer);

	tmp = glowny;

	if (sort == 0) //dodaj na koniec listy
	{
		tmp = ostatni_kontakt(glowny);
		glowny = dodaj_kontakt(imie, nazwisko, grupa, numer, tmp, glowny);
	}
	else //dodaj w odpowiednim miejscu
	{
		while (tmp != NULL & koniec == 0)
		{
			switch (sort)
			{
			case 1: //wg imienia
				porownanie = strcoll(tmp->imie, imie);
				break;
			case 2: //wg nazwiska
				porownanie = strcoll(tmp->nazwisko, nazwisko);
				break;
			default: //wg grupy
				porownanie = strcoll(tmp->grupa, grupa);
				break;
			}

			if (porownanie == 1) //jesli napis w tmp jest pozniej w alfabecie ni¿ nowe
			{
				glowny = dodaj_kontakt(imie, nazwisko, grupa, numer, tmp->poprzedni, glowny);
				koniec = 1;
			}

			if (koniec == 0 & tmp->nastepny == NULL) //jesli koniec kontaktow -> dodaj na ostatnim miejscu
			{
				glowny = dodaj_kontakt(imie, nazwisko, grupa, numer, tmp, glowny);
				koniec = 1;
			}

			tmp = tmp->nastepny;
		}
	}

	return glowny;
}

void main()
{
	Kontakt *glowny = NULL, *tmp;

	setlocale(LC_ALL, "polish_poland"); // polskie znaki
	int wybor_sort = 0, wybor_program = 1;

	glowny = wczytaj_z_pliku(glowny);
	tmp = glowny;

	printf("Lista kontakow:\nimie; nazwisko; grupa; numer\n");

	while (tmp != NULL) //wypisanie wszystkich kontaktow po wczytaniu
	{
		printf("%s; %s; %s; %s\n", tmp->imie, tmp->nazwisko, tmp->grupa, tmp->numer);
		tmp = tmp->nastepny;
	}

	while (wybor_program != 0)
	{
		printf("Menu wyboru:\n1) Usun kontakt\n2) Wyszukaj kontakt\n3) Dodaj kontakt\n4) Sortuj kontakty\n5) Wczytaj kontakty z pliku\n6) Wypisz wszystkie aktualne kontakty\n0) Koniec\n");
		
		if (scanf("%d", &wybor_program) == 0)
		{
			printf("Wprowadzono bledny znak\n");
			break;
		}

		switch (wybor_program)
		{
		case 1: //usun kontakt
			glowny = szukaj_lub_usun(1, glowny);
			
			printf("Poprawnie usunieto kotakt\n");
			break;

		case 2: //wyszukaj kontakt
			glowny = szukaj_lub_usun(0, glowny);
			break;

		case 3: //dodaj kontakt
			glowny = nowy_kontakt(wybor_sort, glowny);
			
			printf("Poprawnie utworzono kontakt\n");
			break;

		case 4: //sortuj kontakty
			printf("Sortuj wedlug:\n1)imion\n2)nazwisk\n3)grup\n");
			scanf("%d", &wybor_sort);

			if (wybor_sort > 3) {
				wybor_sort = 0;
				printf("Wprowadzony bledny znak. Nieposortowano\n");
			}

			glowny = sortuj_kontakty(wybor_sort, glowny);
			printf("Lista kontakow:\nimie; nazwisko; grupa; numer\n");

			tmp = glowny;
			while (tmp != NULL)
			{
				printf("%s; %s; %s; %s\n", tmp->imie, tmp->nazwisko, tmp->grupa, tmp->numer);
				tmp = tmp->nastepny;
			}
			break;

		case 5: //wczytaj z pliku
			glowny = wczytaj_z_pliku(glowny);
			printf("Lista kontakow:\nimie; nazwisko; grupa; numer\n");

			tmp = glowny;
			while (tmp != NULL)
			{
				printf("%s; %s; %s; %s\n", tmp->imie, tmp->nazwisko, tmp->grupa, tmp->numer);
				tmp = tmp->nastepny;
			}
			break;

		case 6: //wypisz wszystkie aktualne kontakty
			printf("Lista kontakow:\nimie; nazwisko; grupa; numer\n");

			tmp = glowny;
			while (tmp != NULL)
			{
				printf("%s; %s; %s; %s\n", tmp->imie, tmp->nazwisko, tmp->grupa, tmp->numer);
				tmp = tmp->nastepny;
			}
			break;

		case 0: //zakoncz program
			break;

		default:
			printf("Wprowadzono bledna liczbe\n");
			break;
		}
	}
}