#include "Gracz.h"
#include "Karta.h"

#include <iostream>
#include <cstring>

using namespace std;

Gracz::Gracz() : punkty(0), ilosc_kart(0), kasyno(nullptr), spasowal(false)
{
}

Gracz::Gracz(Kasyno* tworca, char* _nazwa) : punkty(0), ilosc_kart(0), kasyno(tworca), spasowal(false)
{
	strncpy_s(nazwa, _nazwa, 20);
}

bool Gracz::wezKarte(Karta* _karta)
{
	if (ilosc_kart >= 10) return false;

	karty[ilosc_kart++] = _karta;
	punkty += _karta->getWartosc();
	return true;
}

void Gracz::wyswietl_karty() const
{
	for (int i = 0; i < ilosc_kart; i++) {
		cout << i << ". ";
		karty[i]->wypisz();
		cout << endl;
	}
}

void Gracz::decyzja(bool pasuje)
{
	spasowal = pasuje;
}
