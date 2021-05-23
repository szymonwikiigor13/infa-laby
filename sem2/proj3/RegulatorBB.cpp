#include "RegulatorBB.h"

void RegulatorBB::steruj(float czas)
{
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
