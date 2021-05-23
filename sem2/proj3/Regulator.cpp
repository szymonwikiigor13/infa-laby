#include "Regulator.h"

Regulator::Regulator(float zadanaTemperatura) : zadanaTemperatura(zadanaTemperatura), grzejnik(nullptr), pomieszczenie(nullptr)
{
}

void Regulator::przypiszStale(Grzejnik* grzejnik, Pomieszczenie* pomieszczenie)
{
	this->grzejnik = grzejnik;
	this->pomieszczenie = pomieszczenie;
}
