#pragma once
#include <vector>

#include "Pomieszczenie.h"
#include "Grzejnik.h"
#include "Regulator.h"

using namespace std;

class Symulacja
{
public:
	void iteracja(float czas);
	void przebieg(int iloscIteracji, float czas);
	void zapis(string nazwa);

	Symulacja(Pomieszczenie* pomieszczenie, Grzejnik* grzejnik, Regulator* regulator);
	~Symulacja() = default;

private:
	vector<string> przebiegi;

	Pomieszczenie* pomieszczenie;
	Grzejnik* grzejnik;
	Regulator* regulator;
};

