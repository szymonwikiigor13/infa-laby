#include "Kasyno.h"
#include "Bot.h"

#include <stdlib.h>
#include <string>
#include <fstream>

#include <chrono>
#include <thread>

using namespace std;

int Kasyno::losowa_karta() const
{
	return rand() % 52;
}

void Kasyno::dealokuj(int** wyniki) const
{
	for (int i = 0; i < liczba_graczy; i++) {
		delete[] wyniki[i];
	}

	delete[] wyniki;

	for (int i = 0; i < liczba_graczy; i++) {
		delete gracze[i];
	}

	delete[] gracze;
}

bool Kasyno::wszyscy_pasuja() const
{
	for (int i = 0; i < liczba_graczy; i++) {
		if (!gracze[i]->jest_pas()) {
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

	for (int i = 0; i < liczba_graczy; i++) { // ROZDANIE
		gracze[i]->wezKarte(this->dajKarte());
		gracze[i]->wezKarte(this->dajKarte());

		if (gracze[i]->getPunkty() == 22) {
			perskie[ix++] = gracze[i];
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
			gracze[i]->decyzja(true);
		}
	}

	while (!this->wszyscy_pasuja()) {
		for (int i = 0; i < liczba_graczy; i++) {
			if (!gracze[i]->jest_pas()) {
				cout << "Tura gracza " << gracze[i]->getNazwa() << ":" << endl;
				cout << "Aktualne karty:" << endl;
				gracze[i]->wyswietl_karty();

				cout << "Gracz pasuje? (t/n)" << endl;

				if (gracze[i]->ruch()) {
					Karta* nowa = this->dajKarte();

					if (nowa == nullptr) {
						cout << "Skonczyly sie karty..." << endl;
						break;
					}

					if (gracze[i]->wezKarte(nowa)) {
						cout << "Nowe karty gracza:" << endl;
						gracze[i]->wyswietl_karty();

						if (gracze[i]->getPunkty() > 21) {
							cout << "Gracz przegral..." << endl;
							gracze[i]->decyzja(true);
						}
					}
					else {
						cout << "Gracz przegral..." << endl;
						gracze[i]->decyzja(true);
					}

					this_thread::sleep_for(2000ms);
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
	int** wyniki = new int*[liczba_graczy];
	for (int i = 0; i < liczba_graczy; i++) {
		wyniki[i] = new int[2];
	}

	for (int i = 0; i < liczba_graczy; i++) {
		wyniki[i][0] = gracze[i]->getPunkty();
		wyniki[i][1] = i;
	}

	for (int i = 0; i < liczba_graczy - 1; i++) { // bubble sort
		for (int j = 0; j < liczba_graczy - i - 1; j++) {
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

	if (wyniki[0][0] > 21) {
		cout << "Wszyscy przegrali..." << endl;
		this->zapisz_plik();
		this->dealokuj(wyniki);
		return;
	}

	for (int j = liczba_graczy - 1; j >= 0; j--) {
		int punkty = wyniki[j][0];
		int gracz = wyniki[j][1];

		if (punkty <= 21) { // Pierwszy zwyciezca
			if (j - 1 >= 0) {
				int punkty_wcz = wyniki[j - 1][0];
				int gracz_wcz = wyniki[j - 1][1];

				if (punkty != punkty_wcz) { // Jeden zwyciezca
					cout << "Wygrywa " << gracze[gracz]->getNazwa() << "!" << endl;
					this->zapisz_plik();
					this->dealokuj(wyniki);
					return;
				}
				else { // Remisy
					cout << "Remisuja: " << endl;
					cout << gracze[gracz]->getNazwa() << endl;

					while (j - 1 >= 0) {
						int punkty_wcz = wyniki[j - 1][0];
						int gracz_wcz = wyniki[j - 1][1];

						if (punkty_wcz == punkty) {
							cout << gracze[gracz_wcz]->getNazwa();
							j--;
						}
						else {
							this->zapisz_plik();
							this->dealokuj(wyniki);
							return;
						}
					}
				}
			}
			else {
				cout << "Wygrywa " << gracze[gracz]->getNazwa() << "!" << endl;
				this->zapisz_plik();
				this->dealokuj(wyniki);
				return;
			}
		}
	}
}

void Kasyno::zapisz_plik() const
{
	ofstream plik("wyniki.txt");

	//TODO FORMATOWANIE PLIKU Z WYNIKAMI

	if (plik.is_open()) {
		for (int i = 0; i < liczba_graczy; i++) {
			plik << gracze[i]->getNazwa() << " ";

			for (int j = 0; j < gracze[i]->getIlosc(); j++) {

				char fig = gracze[i]->getKarty()[j].getFigura();
				char kol = gracze[i]->getKarty()[j].getKolor();

				plik << fig << kol << " ";
			}

			plik << gracze[i]->getPunkty() << endl;
		}

		plik.close();
	}
	else {
		cout << "Nie mozna otworzyc pliku do zapisu." << endl;
	}
}

void Kasyno::nowa_gra()
{
	int ilosc_graczy, ilosc_botow;

	cout << "Prosze podac liczbe graczy (maks. 3): " << endl;
	while (true) {
		cin >> ilosc_graczy;

		if (ilosc_graczy > 3 || ilosc_graczy < 0) {
			cout << "Niepoprawna ilosc graczy." << endl;
			continue;
		}

		if (cin.fail() == true) {
			cout << "Wykryto blad!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else break;
	}

	cout << "Prosze podac liczbe botow (maks. 3): " << endl;
	while (true) {
		cin >> ilosc_botow;

		if (ilosc_botow > 3 || ilosc_botow < 0) {
			cout << "Niepoprawna ilosc botow." << endl;
			continue;
		}

		if (cin.fail() == true) {
			cout << "Wykryto blad!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else break;
	}

	liczba_graczy = ilosc_graczy + ilosc_botow;

	gracze = new Gracz*[liczba_graczy];

	for (int i = 0; i < ilosc_graczy; i++) {
		string bufor;

		cout << "Prosze podac nazwe gracza " << i + 1 << ":" << endl;
		while (true) {
			cin >> bufor;
			if (cin.fail() == true) {
				cout << "Wykryto blad!" << endl;
				cin.clear();
				cin.ignore(256, '\n');
			}
			else break;
		}

		if (bufor.size() > 20) {
			i--;
			cout << "Wprowadzono zbyt dluga nazwe..." << endl;
			continue;
		}

		gracze[i] = new Gracz(this, bufor);
	}

	
	for (int i = ilosc_graczy; i < liczba_graczy; i++) {
		int odwaga = rand() % 3 + 1;
		int numer = i - ilosc_graczy + 1;
		string imie;

		switch (odwaga)
		{
		case 1:
			imie = "AgressiveDummy" + to_string(numer);
			break;
		case 2:
			imie = "CasualDummy" + to_string(numer);
			break;
		case 3:
			imie = "ClumsyDummy" + to_string(numer);
			break;
		}

		gracze[i] = new Bot(this, imie, odwaga);
	}

	for (int i = 0; i < 52; i++) {
		zajete[i] = false;
	}

	this->tasuj();
}
