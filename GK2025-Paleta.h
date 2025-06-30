// funkcje do redukcji kolorów i tworzenia palet
#ifndef GK2025_PALETA_H_INCLUDED
#define GK2025_PALETA_H_INCLUDED

#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

void czyscPalete();
void narysujPalete(int px, int py, SDL_Color pal[]);

void narzuconaV1();
void narzuconaV2();
void narzuconaV3();
void paletaNarzucona();
void paletaWykryta();
bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2);
int dodajKolor(SDL_Color kolor);
int sprawdzKolor(SDL_Color kolor);

Uint8 z24Kdo8K(SDL_Color kolor);
SDL_Color z8Kdo24K(Uint8 kolor8bit);


Uint8 z24Kdo5KS(SDL_Color kolor);
SDL_Color z5KSdo24K(Uint8 szary5bit);

SDL_Color z5Kdo24K(Uint8 idx);

void narzucona5KS();
void narysujPalete5KS(int px, int py, SDL_Color paleta[]);
void paletaDedykowana5b();
void narzucona5bColor();
void narzucona5bGrayDither();
void narzucona5bColorDither();
Uint8 z24Kdo5C(SDL_Color c);
SDL_Color z5Cdo24K(Uint8 idx);
void narzucona5bGray();

void paletaMedianCutBW();

#endif // GK2025_PALETA_H_INCLUDED
