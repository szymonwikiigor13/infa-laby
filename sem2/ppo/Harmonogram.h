#pragma once

#include "Czas.h"

using namespace std;

class Harmonogram
{
private:
	Czas* czasy;
	int ilosc;

public:
	~Harmonogram();
	Harmonogram();
	Harmonogram(const Harmonogram& inny);

	Harmonogram& operator=(const Harmonogram& inny);

	Harmonogram* stworzKopie(int n);
	Harmonogram* oknoCzasowe(Czas zakres);

	Czas* podajCzasy();
	Czas& podajJedenCzas(int indeks);
	int podajIlosc();

	void dodajCzas(Czas czas);

	Czas zsumuj();

	void wypisz();
};
