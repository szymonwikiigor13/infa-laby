#pragma once

#include "Regulator.h"

class RegulatorBB : public Regulator
{
public:
	void steruj(float czas) override;

	RegulatorBB(float zadanaTemperatura);
};

