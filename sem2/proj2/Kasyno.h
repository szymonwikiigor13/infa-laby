#pragma once
#include "Karta.h"
#include "Gracz.h"

using namespace std;

class Kasyno
{
private:
	Karta karty[52];
	Gracz gracze[2];
	bool zajete[52];

	int losowa_karta() const;
	bool wszyscy_pasuja() const;
	void podsumuj_wyniki() const;

public:
	Kasyno();

	void tasuj();
	void wypisz() const;
	void graj();
	void nowa_gra();

	Karta* dajKarte();
};

