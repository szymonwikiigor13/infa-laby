#pragma once
#include "Gracz.h"

class Kasyno;

class Bot : public Gracz
{
private:
	int odwaga;

public:
	Bot(Kasyno* tworca, string nazwa, int odwaga);

	bool ruch() override;
};

