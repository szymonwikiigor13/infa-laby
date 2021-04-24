#include "Kasyno.h"

#include <iostream>
#include <time.h>

using namespace std;

int main() {
	srand(time(NULL));

	Kasyno kasyno;
	kasyno.nowa_gra();
	kasyno.graj();
}