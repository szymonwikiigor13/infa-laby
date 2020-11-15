
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNING
//(ax + b) / (cx + d)
void dziedzina(float *min, float *max)
{
    printf("Podaj dolna granice dziedziny: ");  //prosimy o podanie granic funkcji
    scanf_s("%f", min);
    printf_s("Podaj gorna granice dziedziny: ");
    scanf_s("%f", max);
    int chwilowa;
    if (min = max)
    {
        printf_s("Podaj poprawn¹ dziedzinê: ");
        printf("Podaj dolna granice dziedziny: ");  //prosimy o podanie granic funkcji
        scanf_s("%f", min);
        printf_s("Podaj gorna granice dziedziny: ");
        scanf_s("%f", max);
    }
    if (max < min)
    {
        chwilowa = max;
        min = max;
        max = chwilowa;

    }
}

void parametry(float* wspolczynnik[])
{
    printf_s("Mamy funckje okreslona wzorem (ax + b) / (cx + d) gdzie x to zmienna, podaj odpowiednie parametr");
    float a, b, c, d;
    printf_s("Podaj parametr a: ");
    scanf_s("%f", &a);                 //pobranie parametrow od uzytkownika
    printf_s("Podaj parametr b: ");
    scanf_s("%f", &b);
    printf_s("Podaj parametr c: ");
    scanf_s("%f", &c);
    printf_s("Podaj parametr d:");
    scanf_s("%f", &d);                //zapisywanie parametrów w tablicy jako wspó³czynniki
    *wspolczynnik[0] = a;
    *wspolczynnik[1] = b;
    *wspolczynnik[2] = c;
    *wspolczynnik[3] = d;
}
void rozmiartablicy(min,max)
{
    int r;
    float czasprobkowania = (1 / 0.004);
    if (max>0 & min<0)
    {
        r = (| max | +| min | ) / czasprobkowania;
    }
    //jesli jedna dodatknia  druga ujemna
   else {
       r = (| max | -| min | ) / czasprobkowania; }// inne przypadki
    //czas próbkowania to 0.004 w moim przypadku 
    // i trzeba zaokr¹gliæ
    return r;
}

float  generator(float wspolczynniki[], float min, float max, int rozmiar,float* wyniki[])
{
    int i = 0;
    // czemu nie rozmiar?
    //(ax + b) / (cx + d)
    float* wyniki = (float*)malloc(rozmiar * sizeof(float));
    memset(wyniki);

    for (float x = min; x < max && i < rozmiar; x += 0.004, ++i)//podstawaowe zalozenia
    {
        wyniki[i] = (wspolczynniki[0] * x + wspolczynniki[1]) / (wspolczynniki[2] * x + wspolczynniki[3]);  //funcja 
        printf_s("%f\n", wyniki[i]); // wypisywanie
    }
}


void otwieraniepliku(float wyniki[], int i) {
    FILE* wypistablicy;
    wypistablicy = fopen("wypistablicy.csv", "w"); {  //miejsce docelowe pliku w nawiasie
    fprintf(wypistablicy, wyniki[i], char *) ;
    }
    fclose(wypistablicy);
}


void szum(float szumy[] ) {

    srand (time(NULL));
    int e;
    e = 0;
    int losowaliczba = rand();
    float losowyszum = rand();
    
    for (e < 501)
    {
        if (losowaliczba % 5 = 0) {
            if (losowaliczba % 2 <= 1)
            {
                float szumy[e] = (losowyszum % 2);
            }
            else {
                float szumy[e] = -(losowyszum % 2);
            }

        }
        printf_s (szumy[e]);
        e++;
    }


}
void rozmiartablicywynikowej()

int main()

{
    float wspolczynnik[4];
    parametry(&wspolczynnik);
    float min;
    float max;
    dziedzina(&min, &max);
    int rozmiartablicy 
    generator(&wspolczynnik, min, max, );
    float wyniki[i];

    return 0;
}
