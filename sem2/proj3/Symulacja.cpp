#include <iostream> 
#include <string>
#include <fstream>

#include "Symulacja.h"

using namespace std;

void Symulacja::iteracja(float czas)
{
	regulator->steruj(czas);

	float cieploGrzejnika = grzejnik->obliczEmitowaneCieplo();
	pomieszczenie->dodajCieplo(cieploGrzejnika);

	pomieszczenie->aktualizuj(czas);
}

void Symulacja::przebieg(int iloscIteracji, float czas)
{
	for (int i = 0; i < iloscIteracji; i++) {
		this->iteracja(czas);

		cout << "Temperatura pomieszczenia: " << pomieszczenie->getTemperatura() << " [C]" << endl;

		string przebieg = to_string(i) + ";" + to_string(pomieszczenie->getTemperatura()) + ";" + to_string(grzejnik->obliczEmitowaneCieplo()) + "\n";

		przebiegi.push_back(przebieg);
	}
}

void Symulacja::zapis(string nazwaPliku)
{
	ofstream plik(nazwaPliku);

	if (plik.is_open()) {
		plik << "czas;temp;moc\n";

		for (auto p : przebiegi) {
			plik << p;
		}

		plik.close();
	}
	else {
		throw "Nie mozna otworzyc pliku do zapisu";
	}

	przebiegi.clear();
}

Symulacja::Symulacja(Pomieszczenie* pomieszczenie, Grzejnik* grzejnik, Regulator* regulator) : pomieszczenie(pomieszczenie), grzejnik(grzejnik), regulator(regulator)
{
}
