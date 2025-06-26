// metody do algorytmu kwantyzacji (MedianCut)
#ifndef GK2025_MEDIANCUT_H_INCLUDED
#define GK2025_MEDIANCUT_H_INCLUDED

#include <SDL2/SDL.h>

extern int ileKubelkow;
extern Uint8 obrazekS[320*200];
extern SDL_Color obrazekK[320*200];

Uint8 najwiekszaRoznica(int start, int koniec);
int znajdzSasiadaBW(Uint8 wartosc);
int znajdzSasiada(SDL_Color kolor);
void paletaMedianCutBW();
void paletaMedianCut();
void sortujKubelekBW(int start, int koniec);
void sortujKubelek(int start, int koniec, Uint8 sortowanie);
void MedianCutBW(int start, int koniec, int iteracja);
void MedianCut(int start, int koniec, int iteracja);

#endif // GK2025_MEDIANCUT_H_INCLUDED
