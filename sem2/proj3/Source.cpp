#include <iostream>
#include "Pomieszczenie.h"
#include "Symulacja.h"

#include "RegulatorBB.h"
#include "RegulatorPID.h"

using namespace std;

void test() {
	Pomieszczenie pomieszczenie(2.5, 4, 5);
	Grzejnik grzejnik(1800);

	RegulatorBB regulator(18.6);
	//RegulatorPID regulator(18.6, 4, 0.02, 0.1);

	regulator.przypiszStale(&grzejnik, &pomieszczenie);

	Symulacja symulacja(&pomieszczenie, &grzejnik, &regulator);

	symulacja.przebieg(10000, 1.0);

	symulacja.zapis("test.csv");
}

int main() {
	test();
}