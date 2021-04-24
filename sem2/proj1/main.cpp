#include "Czas.h"
#include "Harmonogram.h"

#include <iostream>

using namespace std;

ostream& operator<<(ostream& os, Czas czas) {
	return os << czas.podajGodziny() << ":" << czas.podajMinuty() << ":" << czas.podajSekundy();
}

ostream& operator<<(ostream& os, Harmonogram h) {
	//os to parametr reprezentuj¹cy strumieñ, np. cout
	os << "harmonogram, dlugosc: " << h.podajIlosc() << "\n";

	for (int i = 0; i < h.podajIlosc(); i++) {
		os << h.podajJedenCzas(i) << "\n";
	}

	return os;
}

Harmonogram* przygotujHarmonogram() {
	Czas c1(0, 50, 1), c2(0, -59, 1), c3(100, -59, 1), c4(1, 5, 0), c5(45, 45, 1), c6(0, 13, 0), c7(100, -59, 0), c8(0, -52, 2);

	Harmonogram* temp = new Harmonogram();

	temp->dodajCzas(c1);
	temp->dodajCzas(c2);
	temp->dodajCzas(c3);
	temp->dodajCzas(c4);
	temp->dodajCzas(c5);
	temp->dodajCzas(c6);
	temp->dodajCzas(c7);
	temp->dodajCzas(c8);

	return temp;
}

int main() {
	Harmonogram* h = przygotujHarmonogram(), * temp3, * temp4;

	int wybor = 0, indeks = 0, godz = 0, min = 0, sek = 0;

	while (true) {
		cout << "Menu:\n0. Wyjdz\n1. Wypisz harmonogram z indeksami\n2. Zwiekszanie wybranego czasu\n3. Kopiowanie pierwszych N czasow\n4. Wybierz elementy w zakresie czasowym.\n" << endl;
		cin >> wybor;

		switch (wybor)
		{
		case 0:
			cout << "Koniec programu." << endl;
			return 0;

		case 1:
			h->wypisz();
			break;

		case 2:
			cout << "Podaj indeks czasu: " << endl;
			cin >> indeks;

			if (indeks > h->podajIlosc() || indeks < 0) {
				cout << "Niepoprawny indeks." << endl;
				break;
			}

			cout << "Ile czasu chcesz dodaæ? Najpierw godzina, potem minuta, potem sekunda." << endl;
			cin >> godz;
			cin >> min;
			cin >> sek;

			h->podajJedenCzas(indeks).ustawStan(sek, min, godz);

			cout << "Nowy: ";
			h->podajJedenCzas(indeks).wypisz();
			break;

		case 3:
			cout << "Podaj n pierwszych czasów: " << endl;
			cin >> indeks;

			if (indeks > h->podajIlosc() || indeks < 0) {
				cout << "Niepoprawne n." << endl;
				break;
			}

			cout << "Skopiowany harmonogram: " << endl;
			temp3 = h->stworzKopie(indeks);
			temp3->wypisz();

			delete temp3;
			break;

		case 4:
			cout << "Zdefiniuj zakres. Najpierw godzina, potem minuta, potem sekunda." << endl;
			cin >> godz;
			cin >> min;
			cin >> sek;

			Czas z(sek, min, godz);
			temp4 = h->oknoCzasowe(z);

			cout << "W podanym czasie mieszcza sie: " << endl;

			temp4->wypisz();
			delete temp4;
			break;
		}
	}
}