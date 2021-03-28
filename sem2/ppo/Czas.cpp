#include "Czas.h"

#include <math.h>
#include <iostream>

using namespace std;

Czas::Czas(int sekundy = 0, int minuty = 0, int godziny = 0)
	: sekundy(0)
	, minuty(0)
	, godziny(0)
{
	this->ustawStan(sekundy, minuty, godziny);
}

Czas::Czas()
	: sekundy(0)
	, minuty(0)
	, godziny(0)
{
}

void Czas::ustawStan(int sekundy, int minuty = 0, int godziny = 0)
{
	this->ustawSekundy(sekundy);
	this->ustawMinuty(minuty);
	this->ustawGodziny(godziny);
}

Czas Czas::operator+(Czas czas)
{
	czas.ustawStan(this->podajSekundy(), this->podajMinuty(), this->podajGodziny());

	return czas;
}

bool Czas::operator==(Czas czas)
{
	return czas.podajGodziny() == this->podajGodziny() && czas.podajMinuty() == this->podajMinuty() && czas.podajSekundy() == this->podajSekundy();
}

bool Czas::operator!=(Czas czas)
{
	return !(*this == czas);
}

bool Czas::operator<(Czas czas)
{
	if (this->podajGodziny() > czas.podajGodziny()) return false;
	if (this->podajGodziny() < czas.podajGodziny()) return true;

	if (this->podajMinuty() > czas.podajMinuty()) return false;
	if (this->podajMinuty() < czas.podajMinuty()) return true;

	if (this->podajSekundy() > czas.podajSekundy()) return false;
	if (this->podajSekundy() < czas.podajSekundy()) return true;
}

bool Czas::operator>(Czas czas)
{
	return !(*this == czas) && !(*this < czas);
}

void Czas::ustawSekundy(int sekundy)
{
	this->sekundy += sekundy;
	this->przelicz();
}

void Czas::ustawMinuty(int minuty)
{
	this->minuty += minuty;
	this->przelicz();
}

void Czas::ustawGodziny(int godziny)
{
	this->godziny += godziny;
	this->przelicz();
}

void Czas::przelicz()
{
	this->sekundy += this->minuty * 60 + this->godziny * 3600;

	this->godziny = floor(this->sekundy / 3600);
	this->sekundy -= this->godziny * 3600;

	this->minuty = floor(this->sekundy / 60);
	this->sekundy -= this->minuty * 60;
}

int Czas::podajSekundy()
{
	return this->sekundy;
}

int Czas::podajMinuty()
{
	return this->minuty;
}

int Czas::podajGodziny()
{
	return this->godziny;
}

void Czas::wypisz()
{
	cout << this->podajGodziny() << ":" << this->podajMinuty() << ":" << this->podajSekundy() << endl;
}
