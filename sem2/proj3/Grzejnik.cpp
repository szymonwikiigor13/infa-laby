#include "Grzejnik.h"

Grzejnik::Grzejnik(float mocNominalna): mocNominalna(mocNominalna), poziomMocy(0)
{
	if (mocNominalna <= 0) {
		throw "Moc nominalna jest mniejsza badz rowna zeru";
	}
}

void Grzejnik::ustawPoziomMocy(float poziomMocy)
{
	if (poziomMocy < 0 || poziomMocy > 1) {
		throw "Niepoprawny poziom mocy";
	}

	this->poziomMocy = poziomMocy;
}

float Grzejnik::podajPoziomMocy() const
{
	return poziomMocy;
}

float Grzejnik::obliczEmitowaneCieplo() const
{
	return mocNominalna * poziomMocy;
}
