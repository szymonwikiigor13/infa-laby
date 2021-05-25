#include <iostream>

#include "Pomieszczenie.h"
#include "Symulacja.h"

#include "RegulatorBB.h"
#include "RegulatorPID.h"

using namespace std;

void test() {
	Pomieszczenie pomieszczenie(2.5, 4, 5);
	Grzejnik grzejnik(2000);

	Symulacja symulacja(&pomieszczenie, &grzejnik, nullptr);

	grzejnik.ustawPoziomMocy(0.5);

	symulacja.przebieg(1000, 1.0);

	grzejnik.ustawPoziomMocy(1);

	symulacja.przebieg(1000, 1.0);

	symulacja.zapis("test.csv");
}

void menu() {
	Pomieszczenie pomieszczenie(2.5, 4, 5);
	Grzejnik grzejnik(1800);
	int wybor = -1;

	while (true)
	{
		Regulator* regulator = nullptr;

		float temperatura = 0;

		cout << "Podaj oczekiwana temperature w [C]: " << endl;
		cin >> temperatura;

		if (cin.fail()) {
			cout << "Wykryto blad!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}

		cout << "Wybierz regulator do symulacji:" << endl;
		cout << "1 - regulator BB" << endl;
		cout << "2 - regulator PID" << endl;
		cin >> wybor;

		if (cin.fail()) {
			cout << "Wykryto blad!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}

		try {
			switch (wybor) {
			case 1:
				regulator = new RegulatorBB(temperatura);
				break;

			case 2:
				regulator = new RegulatorPID(temperatura, 4, 0.02, 0.1);
				break;

			default:
				throw exception("Niepoprawny wybor!");
			}

			regulator->przypiszStale(&grzejnik, &pomieszczenie); //tutaj powodujemy blad

			Symulacja symulacja(&pomieszczenie, &grzejnik, regulator);

			symulacja.przebieg(1000, 1.0);

			symulacja.zapis("symulacja.csv");

			cout << "Przebieg zakonczony - wyniki w pliku 'symulacja.csv'" << endl;
		}
		catch (exception exception) {
			cout << exception.what() << endl;
		}

		cout << "Wpisz '0' aby zakonczyc program lub inna cyfre aby przeprowadzic symulacje dla innych parametrow." << endl;
		cin >> wybor;
		if (cin.fail()) {
			cout << "Wykryto blad!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}

		delete regulator;

		if (wybor == 0) {
			break;
		}
	}
}

int main() {
	menu();
	//test();
}