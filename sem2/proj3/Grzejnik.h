#pragma once

class Grzejnik
{
public:
	Grzejnik(float mocNominalna);

	void ustawPoziomMocy(float poziomMocy);
	float podajPoziomMocy() const;

	float obliczEmitowaneCieplo() const;

private:
	float mocNominalna;
	float poziomMocy;
};
