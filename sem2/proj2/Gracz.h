#pragma once

class Karta;
class Kasyno;

class Gracz
{
private:
	char nazwa[20] = { 0 };
	Kasyno* kasyno;
	Karta* karty[10];

	int punkty;
	int ilosc_kart;

	bool spasowal;

public:
	Gracz();
	Gracz(Kasyno* tworca, char* nazwa);

	char* getNazwa() const { return (char*) &nazwa; };
	int getPunkty() const { return punkty; };
	int getIlosc() const { return ilosc_kart; };
	bool jest_pas() const { return spasowal; };

	bool wezKarte(Karta* _karta);
	void wyswietl_karty() const;
	void decyzja(bool pasuje);
};

