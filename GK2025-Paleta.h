// funkcje do redukcji kolorów i tworzenia palet
#ifndef GK2025_PALETA_H_INCLUDED
#define GK2025_PALETA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
using namespace std;

void czyscPalete();
void narysujPalete3b(int px, int py, SDL_Color pal3b[]);
void narysujPalete(int px, int py, SDL_Color pal[]);

#endif // GK2025_PALETA_H_INCLUDED
