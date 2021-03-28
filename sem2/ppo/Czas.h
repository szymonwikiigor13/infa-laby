#pragma once
#include <iostream>

using namespace std;

class Czas
{
private:
	int sekundy;
	int minuty;
	int godziny;

	void ustawSekundy(int sekundy);
	void ustawMinuty(int minuty);
	void ustawGodziny(int godziny);

	void przelicz();

public:
	Czas(int sekundy, int minuty, int godziny);
	Czas();

	void ustawStan(int sekundy, int minuty, int godziny);

	Czas operator+(Czas czas);
	bool operator==(Czas czas);
	bool operator!=(Czas czas);
	bool operator<(Czas czas);
	bool operator>(Czas czas);

	int podajSekundy();
	int podajMinuty();
	int podajGodziny();

	void wypisz();
};
