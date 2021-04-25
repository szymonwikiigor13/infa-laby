#pragma once
#include <string>

using namespace std;

class Karta;
class Kasyno;

class Gracz
{
private:
	string nazwa;
	Kasyno* kasyno;
	Karta* karty[10];

	int punkty;
	int ilosc_kart;

	bool spasowal;

public:
	Gracz();
	Gracz(Kasyno* tworca, string nazwa);

	string getNazwa() const { return nazwa; };
	Karta* getKarty() const { return (Karta*) karty; };
	int getPunkty() const { return punkty; };
	int getIlosc() const { return ilosc_kart; };
	bool jest_pas() const { return spasowal; };

	virtual bool ruch();

	bool wezKarte(Karta* _karta);
	void wyswietl_karty() const;
	void decyzja(bool pasuje);
};

