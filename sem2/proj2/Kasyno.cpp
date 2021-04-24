#include "Kasyno.h"

#include <stdlib.h>

int Kasyno::losowa_karta() const
{
	return rand() % 52;
}

bool Kasyno::wszyscy_pasuja() const
{
	for (int i = 0; i < 2; i++) {
		if (!gracze[i].jest_pas()) {
			return false;
		}
	}

	return true;
}



Kasyno::Kasyno()
{
	int ix = 0;

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 4; j++) {
			karty[ix++] = Karta(j, i);
		}
	}

	for (int i = 0; i < 52; i++) {
		zajete[i] = false;
	}
}

void Kasyno::tasuj()
{
	for (int i = 0; i < 100; i++) {
		int pierw = this->losowa_karta();
		int drug = this->losowa_karta();

		if (pierw == drug) { //Powtarzamy losowanie dla tej samej karty
			i--;
			continue; //continue to taki break ktory nie przerywa, tylko wymusza kolejne przejscie petli
		}

		Karta temp = karty[pierw];

		karty[pierw] = karty[drug];
		karty[drug] = temp;
	}
}

void Kasyno::wypisz() const
{
	for (int i = 0; i < 52; i++) {
		cout << i << ". ";
		karty[i].wypisz();
		cout << endl;
	}
}

Karta* Kasyno::dajKarte()
{
	int ix = this->losowa_karta();

	int liczba_cykli = 0;
	while (zajete[ix] == true) {
		if (ix == 51) {
			ix = 0;
		}
		else {
			ix++;
		}

		liczba_cykli++;
		if (liczba_cykli > 52) {
			return nullptr;
		}
	}

	zajete[ix] = true;
	return &karty[ix];
}

void Kasyno::graj()
{
	Gracz* perskie[2] = { nullptr };
	int ix = 0;

	for (int i = 0; i < 2; i++) { // ROZDANIE
		gracze[i].wezKarte(this->dajKarte());
		gracze[i].wezKarte(this->dajKarte());

		if (gracze[i].getPunkty() == 22) {
			perskie[ix++] = &gracze[i];
		}
	}

	if (perskie[0] != nullptr && perskie[1] != nullptr) {
		cout << "Perskie oczko graczy " << perskie[0]->getNazwa() << " i " << perskie[1]->getNazwa() << " - remis!" << endl;
	}
	else if (perskie[0] != nullptr) {
		cout << "Perskie oczko gracza " << perskie[0]->getNazwa() << " - wygrana!" << endl;
	}

	if (perskie[0] != nullptr) {
		for (int i = 0; i < 2; i++) { // AUTO PAS
			gracze[i].decyzja(true);
		}
	}

	while (!this->wszyscy_pasuja()) {
		for (int i = 0; i < 2; i++) {
			if (!gracze[i].jest_pas()) {
				cout << "Tura gracza " << gracze[i].getNazwa() << ":" << endl;
				cout << "Aktualne karty:" << endl;
				gracze[i].wyswietl_karty();

				char decyzja;
				cout << "Gracz pasuje? (t/n)" << endl;
				cin >> decyzja;

				if (decyzja == 't') {
					gracze[i].decyzja(true);
				}
				else {
					Karta* nowa = this->dajKarte();

					if (nowa == nullptr) {
						cout << "Skonczyly sie karty..." << endl;
						break;
					}

					if (gracze[i].wezKarte(nowa)) {
						cout << "Nowe karty gracza:" << endl;
						gracze[i].wyswietl_karty();

						if (gracze[i].getPunkty() > 21) {
							cout << "Gracz przegral..." << endl;
							gracze[i].decyzja(true);
						}
					}
					else {
						cout << "Gracz przegral..." << endl;
						gracze[i].decyzja(true);
					}
				}
			}
		}
	}

	this->podsumuj_wyniki();
}

void Kasyno::podsumuj_wyniki() const
{
	//i  0  1  2                   i  0  1  2
	//p|12|20|18| -> sortowanie -> p|12|18|20|
	//g| 0| 1| 2|                  g| 0| 2| 1|
	const int ilosc_graczy = 2;

	int wyniki[2][2] = { 0 };

	for (int i = 0; i < 2; i++) {
		wyniki[i][0] = gracze[i].getPunkty();
		wyniki[i][1] = i;
	}

	for (int i = 0; i < ilosc_graczy - 1; i++) {
		for (int j = 0; j < ilosc_graczy - i - 1; j++) {
			if (wyniki[j][0] > wyniki[j + 1][0]) {
				int temp[2];

				temp[0] = wyniki[j][0];
				temp[1] = wyniki[j][1];

				wyniki[j][0] = wyniki[j + 1][0];
				wyniki[j][1] = wyniki[j + 1][1];

				wyniki[j + 1][0] = temp[0];
				wyniki[j + 1][1] = temp[1];
			}
		}
	}

	//TODO get punkty

	int maks_wynik = -1;
	bool remis = false;
	for (int j = ilosc_graczy - 1; j >= 0; j--) {
		int punkty = wyniki[j][0];
		int gracz = wyniki[j][1];

		if (punkty <= 21 && maks_wynik == -1) {
			maks_wynik = punkty;

			if (j - 1 >= 0) {
				int punkty_wcz = wyniki[j - 1][0];
				int gracz_wcz = wyniki[j - 1][1];

				if (maks_wynik != punkty_wcz) {
					cout << "Wygrywa " << gracze[gracz].getNazwa() << "!" << endl;
					return;
				}
				else {
					cout << "Remisuj¹: ";
				}
			}

			cout << "Wygrywa " << gracze[gracz].getNazwa() << endl;
		}
		else if (punkty == maks_wynik) {
			cout << "Wygrywa " << gracze[gracz].getNazwa() << endl;
			remis = true;
		}

	}
}

void Kasyno::nowa_gra()
{
	char bufor[20];

	for (int i = 0; i < 2; i++) {
		cout << "Prosze podac nazwe gracza " << i + 1 << ":" << endl;
		cin >> bufor;

		gracze[i] = Gracz(this, bufor);
	}

	for (int i = 0; i < 52; i++) {
		zajete[i] = false;
	}

	this->tasuj();
}
