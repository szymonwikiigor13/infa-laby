#include <stdio.h>

struct zespolona {
	float re;
	float im;
	int blad;
};

typedef struct zespolona Zespolona;

struct wezel {
	Zespolona* dane;
	struct wezel* poprzedni;
};

typedef struct wezel Stos;

Stos* stos_nowy() {
	Stos* nowy = (Stos*)malloc(sizeof(Stos));
	nowy->poprzedni = NULL;
	nowy->dane = NULL;

	return nowy;
}

int stos_is_empty(Stos** stos) {
	return (*stos)->dane == NULL && (*stos)->poprzedni == NULL;
}

void stos_push(Stos** stos, Zespolona* element) {
	if (stos_is_empty(stos)) {
		(*stos)->dane = element;
		return;
	}

	Stos* nowy = stos_nowy();

	nowy->dane = (Zespolona*)malloc(sizeof(Zespolona));
	nowy->dane = element;
	nowy->poprzedni = *stos;
	*stos = nowy;
}

Zespolona* stos_pop(Stos** stos) {
	if (stos_is_empty(stos)) {
		return NULL;
	}

	Zespolona* wynik = (*stos)->dane;
	Stos* poprzedni = (*stos)->poprzedni;

	if (poprzedni != NULL) {
		free(*stos);
		*stos = poprzedni;
	}
	else {
		(*stos)->dane = NULL;
	}

	return wynik;
}

void stos_clear(Stos** stos) {
	if (stos_is_empty(stos)) {
		return;
	}

	Zespolona* wyjscie;

	while ((wyjscie = stos_pop(stos)) != NULL) {
		if (wyjscie != NULL) {
			free(wyjscie);
		}
	}
}

void stos_wyswietl(Stos** stos) {
	Stos* wezel = *stos;

	for (int i = 1;; i++) {
		printf("%d. %f %fi\n", i, wezel->dane->re, wezel->dane->im);

		wezel = wezel->poprzedni;

		if (wezel == NULL) {
			return;
		}
	}
}

Zespolona* dodawanie(Zespolona* p, Zespolona* d)
{
	Zespolona* wynik = (Zespolona*)malloc(sizeof(Zespolona));
	wynik->blad = 0;

	wynik->re = p->re + d->re;
	wynik->im = p->im + d->im;

	return wynik;
}

Zespolona* odejmowanie(Zespolona* p, Zespolona* d)
{
	Zespolona* wynik = (Zespolona*)malloc(sizeof(Zespolona));
	wynik->blad = 0;

	wynik->re = p->re - d->re;
	wynik->im = p->im - d->im;

	return wynik;
}

Zespolona* mnozenie(Zespolona* p, Zespolona* d) {
	Zespolona* wynik = (Zespolona*)malloc(sizeof(Zespolona));
	wynik->blad = 0;

	wynik->re = p->re * d->re - p->im * d->im;
	wynik->im = p->re * d->im + p->im * d->re;

	return wynik;
}

Zespolona* dzielenie(Zespolona* p, Zespolona* d) {
	Zespolona* wynik = (Zespolona*)malloc(sizeof(Zespolona));
	wynik->blad = 0;

	if (d->re == 0.f && d->im == 0.f) {
		wynik->blad = 1;
		return wynik;
	}

	float dol = (d->re * d->re + d->im * d->im);

	wynik->re = ((p->re * d->re) + (p->im * d->im)) / dol;
	wynik->im = ((p->im * d->re) - (p->re * d->im)) / dol;

	return wynik;
}

Zespolona* z_napisu(char* napis) {
	Zespolona* wynik = (Zespolona*)malloc(sizeof(Zespolona));
	wynik->blad = 0;

	int wczytane = sscanf_s(napis, "%f %f i", &wynik->re, &wynik->im);

	if (wczytane == 2) {
		return wynik;
	}

	wczytane = sscanf_s(napis, "%f", &wynik->re);
	wynik->im = 0;

	if (wczytane == 0) {
		wynik->blad = 1;
	}

	return wynik;
}

int main() {
	Stos* stos = stos_nowy();
	char bufor[50] = { 0 };

	printf("Wprowadz liczbe zespolona w formacie 're im i' lub jedna z operacji +, -, *, /.\n");
	printf("Wpisz 'exit' aby wyjsc.\n");

	while (1) {
		fgets(bufor, 50, stdin);

		Zespolona* wczytana = z_napisu(bufor);

		if (wczytana->blad) {
			if (strcmp(bufor, "+\n") == 0) {
				Zespolona* pierwsza = stos_pop(&stos);
				Zespolona* druga = stos_pop(&stos);

				if (pierwsza == NULL || druga == NULL) {
					printf("Zbyt malo elementow na stosie\n");
					stos_clear(&stos);

					if (pierwsza != NULL) {
						free(pierwsza);
					}
					if (druga != NULL) {
						free(druga);
					}
				}
				else {
					Zespolona* wynik = dodawanie(pierwsza, druga);
					free(pierwsza);
					free(druga);
					stos_push(&stos, wynik);
					printf("Wykonano obliczenie, wynik = %f %fi\n", wynik->re, wynik->im);
				}
			}
			else if (strcmp(bufor, "-\n") == 0) {
				Zespolona* pierwsza = stos_pop(&stos);
				Zespolona* druga = stos_pop(&stos);

				if (pierwsza == NULL || druga == NULL) {
					printf("Zbyt malo elementow na stosie\n");
					stos_clear(&stos);

					if (pierwsza != NULL) {
						free(pierwsza);
					}
					if (druga != NULL) {
						free(druga);
					}
				}
				else {
					Zespolona* wynik = odejmowanie(pierwsza, druga);
					free(pierwsza);
					free(druga);
					stos_push(&stos, wynik);
					printf("Wykonano obliczenie, wynik = %f %fi\n", wynik->re, wynik->im);
				}
			}
			else if (strcmp(bufor, "*\n") == 0) {
				Zespolona* pierwsza = stos_pop(&stos);
				Zespolona* druga = stos_pop(&stos);

				if (pierwsza == NULL || druga == NULL) {
					printf("Zbyt malo elementow na stosie\n");
					stos_clear(&stos);

					if (pierwsza != NULL) {
						free(pierwsza);
					}
					if (druga != NULL) {
						free(druga);
					}
				}
				else {
					Zespolona* wynik = mnozenie(pierwsza, druga);
					free(pierwsza);
					free(druga);
					stos_push(&stos, wynik);
					printf("Wykonano obliczenie, wynik = %f %fi\n", wynik->re, wynik->im);
				}
			}
			else if (strcmp(bufor, "/\n") == 0) {
				Zespolona* pierwsza = stos_pop(&stos);
				Zespolona* druga = stos_pop(&stos);

				if (pierwsza == NULL || druga == NULL) {
					printf("Zbyt malo elementow na stosie, stos zostanie wyczyszczony\n");
					stos_clear(&stos);

					if (pierwsza != NULL) {
						free(pierwsza);
					}
					if (druga != NULL) {
						free(druga);
					}
				}
				else {
					Zespolona* wynik = dzielenie(pierwsza, druga);
					free(pierwsza);
					free(druga);

					if (wynik->blad) {
						printf("Blad dzielenia przez zero, stos zostanie wyczyszczony\n");
						stos_clear(&stos);
					}
					else {
						stos_push(&stos, wynik);
						printf("Wykonano obliczenie, wynik = %f %fi\n", wynik->re, wynik->im);
					}
				}
			}
			else if (strcmp(bufor, "exit\n") == 0) {
				printf("Program zostanie zamkniety\n");
				stos_clear(&stos);
				free(stos);
				return 0;
			}
			else {
				free(wczytana);
				printf("Blad\n");
			}
		}
		else {
			stos_push(&stos, wczytana);

			printf("Aktualny stan stosu: \n");
			stos_wyswietl(&stos);
		}

	}
}