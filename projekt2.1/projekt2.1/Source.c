#include<stdio.h>
#include <stdlib.h>


//#include <cctype>
#define _CRT_SECURE_NO_WARNINGS



void odczyt_pliku()
{// obs³uga komentarzy do zrobienia
	struct obraz
	{
		int x;//8
		int y;//8// wymiary na pocz¹tek
		int max_szarosc;// jedna wartosc do ktorej porownojemy
		int** odcien_szarosci;// tyle ,,pikseli''
		

	};
	char nazwa_pliku;
	printf("Podaj nazwe pliku z rozszerzeniem PMG");
	scanf("%s", &nazwa_pliku);

	struct obraz odczytany_obraz;
	odczytany_obraz.x;
	
	odczytany_obraz.y; 
	// wartosci z palca ? czy jak je wyciagnac 
	printf("Podaj skale szarosci od 1 do 65535 ");
	scanf("%d", &odczytany_obraz.max_szarosc);
	odczytany_obraz.odcien_szarosci = malloc(odczytany_obraz.x *sizeof(*odczytany_obraz.odcien_szarosci));
	int  i;
	for (i = 0; i < odczytany_obraz.x; i++)
	{
		odczytany_obraz.odcien_szarosci[i] = malloc(odczytany_obraz.y * sizeof(odczytany_obraz.odcien_szarosci));
	}// moze byc ?
	//dynamiczna alokacja
	 FILE* odczyt_do_tabeli;
	 odczyt_do_tabeli= fopen(nazwa_pliku, "r");
	 if (nazwa_pliku == 0)
	 {
		 abort;
	 }
	 char p;
	 char pprim="P";
	 int standard;
	 char bialy_znak;
	 fscanf(odczyt_do_tabeli,"%s",&p);
	 if (p != pprim)
	 {
		 printf("Zly format lub plik uszkodzony");
		 abort;
	 }
	 fscanf(odczyt_do_tabeli, "%d", &standard);
	 if (standard != 2)
	 {
		 printf("Zly format lub plik uszkodzony");
		 abort;
	 }
	 fscanf(odczyt_do_tabeli, "%s", &bialy_znak);
	//if (isspace(bialy_znak)==0)
	// {
	//	 printf("Zly format lub plik uszkodzony");
	//	 abort;
	// }
	 // sprawdzenie bialego znaku
	 int temp[8][8];//przyklad
	 while (!feof(nazwa_pliku))
	 {
		 temp[8][8]=fscanf(odczyt_do_tabeli,"%d",&odczytany_obraz.odcien_szarosci);// samo odpowienio zapisze ?
	 }
	 printf(temp);// ca³a sie wyswietli czy trzeba robic petle
	 fclose(nazwa_pliku);
}


//struct obraz
//{
//	int x;//8
//	int y;//8// wymiary na pocz¹tek
//	int max_szarosc;// jedna wartosc do ktorej porownojemy
//	int odcien_szarosci[8][8];// tyle ,,pikseli''
//
//};


void zapis_do_pliku(odczyta)
{
	char nazwa;
	printf("Podaj nazwê pliku który ma powstaæ", &nazwa);
	//(char* nazwa, float* wyniki, int rozmiar) {
		FILE* wypis_tablicy;

		wypis_tablicy = fopen(nazwa, "w");  //miejsce docelowe pliku w nawiasie // jesli sie nie otworzy zwraca null
		if (wypis_tablicy == 0) // sprawdzamy dla dla pliku, a nie dla nazwa
		{
			abort();// bo exit zwraca wartosc
		}
		//zabez
		// wypisac jakos piksele, w jaki sposób?
		//for()
		//{
		//	fpintf(wypis_tablicy,"%d\n",*odczytany_obraz.odcien_szarosci);
		//}
		

		fclose(wypis_tablicy);
	}




























void menu()
{
	char napis[50] = { 0 };

	while (1) {
		printf("Menu:\n1Odczyt pliku\n2....\n3Zapis do pliku\n4.Zamknij\n");
		scanf("%s", napis);

		int wybor = atoi(napis); //ascii na inta

		switch (wybor) {
		case 0: // wynik funkcji atoi jesli nie mozna zamienic napisu na int jest rowny 0
			printf("Wprowadziles napis zamiast liczby, sprobuj ponownie\n");
			break;

		case 1:
			odczyt_pliku();
			break;

		case 2:
			//();
			break;

		case 3:
			zapis_do_pliku();
			break;

		case 4:
			return;

		default: // uzytkownik wprowadzil liczbe ale nie ma takiej opcji
			printf("Niepoprawny wybor, sprobuj ponownie\n");
			break;
		}
	}
}

void main()
{
	menu();
}