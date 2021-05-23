#include "RegulatorPID.h"

void RegulatorPID::steruj(float czas)
{
	float zmierzona = this->podajPomieszczenie()->getTemperatura();

	float e = (this->podajZadanaTemperature() - zmierzona);
	float up = kp * e;

	float calkaE = 0.5 * e * e + (e * czas);

	float ui = ki * calkaE;

	float deltaE = (e - ostatnieE) / czas;
	float ud = kd * deltaE;

	ostatnieE = e;

	float u = up + ui + ud;

	if (u < 0) u = 0;
	else if (u > 1) u = 1;
	else if (u < 0.5) u = 0;
	else if (u > 0.5) u = 1;

	this->podajGrzejnik()->ustawPoziomMocy(u);
}

RegulatorPID::RegulatorPID(float zadanaTemperatura, float kp, float ki, float kd) : Regulator(zadanaTemperatura), kp(kp), ki(ki), kd(kd), ostatnieE(0)
{
}
