#pragma once
#include "Karta.h"
#include "Gracz.h"

using namespace std;

class Kasyno
{
private:
	Karta karty[52];
	Gracz** gracze;
	bool zajete[52];
	int liczba_graczy;

	int losowa_karta() const;
	void dealokuj(int** wyniki) const;
	bool wszyscy_pasuja() const;
	void podsumuj_wyniki() const;
	void zapisz_plik() const;

public:
	Kasyno();

	void tasuj();
	void wypisz() const;
	void graj();
	void nowa_gra();

	Karta* dajKarte();
};

