#include "Bot.h"
#include <iostream>

Bot::Bot(Kasyno* tworca, string nazwa, int odwaga) : Gracz(tworca, nazwa), odwaga(odwaga)
{
}

bool Bot::ruch()
{
	int granica = 0;
	switch (odwaga)
	{
	case 1:
		granica = 17; break;
	case 2:
		granica = 15; break;
	case 3:
		granica = 13; break;
	}

	if (getPunkty() <= granica) {
		cout << "n" << endl;
		return true;
	}
	else {
		cout << "t" << endl;
		decyzja(true);
		return false;
	}
}
