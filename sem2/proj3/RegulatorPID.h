#pragma once
#include "Regulator.h"

class RegulatorPID : public Regulator
{
public:
	void steruj(float czas) override;

	RegulatorPID(float zadanaTemperatura, float kp, float ki, float kd);

private:
	float kp;
	float ki;
	float kd;
	float ostatnieE;
};

