#include "Gracz.h"
#include "Karta.h"

#include <iostream>
#include <cstring>

using namespace std;

Gracz::Gracz() : punkty(0), ilosc_kart(0), kasyno(nullptr), spasowal(false)
{
}

Gracz::Gracz(Kasyno* tworca, string _nazwa) : punkty(0), ilosc_kart(0), kasyno(tworca), spasowal(false), nazwa(_nazwa)
{
}

bool Gracz::ruch()
{
	string decyzja;

	while (true) {
		cin >> decyzja;
		if (cin.fail() == true) {
			cout << "Wykryto blad!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else break;
	}

	if (decyzja[0] == 't') {
		this->decyzja(true);
		return false;
	}

	return true;
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
