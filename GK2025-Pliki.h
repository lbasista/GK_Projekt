// GK2025_PLIKI_H_INCLUDED
// funkcje do operacji na plikach
#ifndef GK2025_PLIKI_H_INCLUDED
#define GK2025_PLIKI_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <fstream>
#include <SDL2/SDL.h>

void zapiszPlikv0();
void zapisPlik();

void odczytajPlik();
void zapiszPlik8();

void zapiszPlik5Bit(const char* filename);
void odczytajPlik5Bit(const char* filename);

#endif // GK2025_PLIKI_H_INCLUDED

