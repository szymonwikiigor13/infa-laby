#pragma once
#include "Grzejnik.h"
#include "Pomieszczenie.h"

class Regulator
{
public:
	virtual void steruj(float czas) = 0;
	float podajZadanaTemperature() const { return zadanaTemperatura; };

	Grzejnik* podajGrzejnik() const { return grzejnik; };
	Pomieszczenie* podajPomieszczenie() const { return pomieszczenie; };

	void przypiszStale(Grzejnik* grzejnik, Pomieszczenie* pomieszczenie);

	Regulator(float zadanaTemperatura);
	~Regulator() = default;

private:
	float zadanaTemperatura;

	Grzejnik* grzejnik;
	Pomieszczenie* pomieszczenie;
};
