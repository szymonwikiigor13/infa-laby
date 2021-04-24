#include "Harmonogram.h"

#include <iostream>

using namespace std;

Harmonogram::~Harmonogram()
{
	delete[] this->czasy;
	cout << "Zwolniono harmonogram" << endl;
}

Harmonogram::Harmonogram()
	: czasy(nullptr)
	, ilosc(0)
{
}

Harmonogram::Harmonogram(const Harmonogram& inny) // konstruktor kopiujacy - alokuje tyle pamieci co w drugim i przepisuje dane | Harmonogram h1 = h2;
{
	this->ilosc = inny.ilosc;

	this->czasy = new Czas[this->ilosc];

	for (int i = 0; i < this->ilosc; i++) {
		this->czasy[i] = inny.czasy[i];
	}
}

Harmonogram& Harmonogram::operator=(const Harmonogram& inny) // operator przypisania podmienia wartosci | h1 = h2;
{
	if (&inny == this) return *this; // jesli przypisujesz obiekt temu samemu obiektowi - nie rob nic
	delete[] this->czasy;

	this->ilosc = inny.ilosc;
	this->czasy = new Czas[this->ilosc];

	for (int i = 0; i < this->ilosc; i++) {
		this->czasy[i] = inny.czasy[i];
	}

	return *this;
}

Harmonogram* Harmonogram::stworzKopie(int n)
{
	Harmonogram* temp = new Harmonogram();

	if (n > this->ilosc) return temp;

	temp->ilosc = n;
	temp->czasy = new Czas[n];

	for (int i = 0; i < n; i++) {
		temp->czasy[i] = this->czasy[i];
	}

	return temp;
}

Harmonogram* Harmonogram::oknoCzasowe(Czas zakres)
{
	Harmonogram* temp = new Harmonogram();

	for (int i = 0; i < this->podajIlosc(); i++) {
		Czas c = this->podajJedenCzas(i);
		
		if ((temp->zsumuj() + c) < zakres) {
			temp->dodajCzas(c);
		}
		else {
			return temp;
		}
	}

	return temp;
}

Czas* Harmonogram::podajCzasy()
{
	return this->czasy;
}

Czas& Harmonogram::podajJedenCzas(int indeks)
{
	return czasy[indeks];
}

int Harmonogram::podajIlosc()
{
	return this->ilosc;
}

void Harmonogram::dodajCzas(Czas czas)
{
	if (this->czasy == nullptr) {
		this->czasy = new Czas[1];
		this->czasy[0] = czas;
		this->ilosc = 1;
	}
	else {
		Czas* temp = new Czas[this->podajIlosc() + 1];

		for (int i = 0; i < this->podajIlosc(); i++) {
			temp[i] = this->czasy[i];
		}

		temp[this->podajIlosc()] = czas;

		delete[] this->czasy;
		this->czasy = temp;
		this->ilosc += 1;
	}
}

Czas Harmonogram::zsumuj()
{
	Czas temp;

	for (int i = 0; i < this->podajIlosc(); i++) {
		temp = temp + this->podajJedenCzas(i);
	}

	return temp;
}

void Harmonogram::wypisz()
{
	cout << "harmonogram, dlugosc: " << this->podajIlosc() << "\n";

	for (int i = 0; i < this->podajIlosc(); i++) {
		cout << i << ". ";
		this->podajJedenCzas(i).wypisz();
	}

	cout << endl;
}
