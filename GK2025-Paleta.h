// funkcje do redukcji kolorów i tworzenia palet
#ifndef GK2025_PALETA_H_INCLUDED
#define GK2025_PALETA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
using namespace std;

void narzuconaV1();
void narzuconaV2();
void narzuconaV3();
void narzuconaV4();
void paletaNarzucona();
void paletaWykryta();

Uint8 z24Kdo5KS(SDL_Color kolor);
SDL_Color z5KSdo24K(Uint8 szary5bit);
void narzucona5KS();
void narysujPalete5KS(int px, int py, int rozmiarBloku);

paletaMedianCutBW();
narysujPalete3b(int px, int py, SDL_Color pal3b[]);
#endif // GK2025_PALETA_H_INCLUDED
