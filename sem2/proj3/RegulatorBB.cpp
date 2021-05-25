#include <exception>

#include "RegulatorBB.h"

using namespace std;

void RegulatorBB::steruj(float czas)
{
	if (!this->podajPomieszczenie() || !this->podajGrzejnik()) {
		throw exception("Nie skonfigurowano powiazan");
	}

	float zmierzona = this->podajPomieszczenie()->getTemperatura();

	if (zmierzona < this->podajZadanaTemperature()) {
		this->podajGrzejnik()->ustawPoziomMocy(1);
	}
	else {
		this->podajGrzejnik()->ustawPoziomMocy(0);
	}
}

RegulatorBB::RegulatorBB(float zadanaTemperatura) : Regulator(zadanaTemperatura)
{
}
