// metody do algorytmu kwantyzacji (MedianCut)
#include "GK2025-MedianCut.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"
#unclude "GK2025-Paleta.h"

using namespace std;

void paletaMedianCutBW(){
  ileKubelkow = 0;
  ileKolorow = 0;
  czyscPalete();
  SDL_COLOR kolor;

  int szary = 0;
  int numer = 0;
  int indeks = 0;

  for(int y=0; y<wysokosc/2; y++){
     for(int x=0; x<szerokosc/2; x++){
        kolor = getPixel(x, y);
        szary = 0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b;
        obrazekS[numer] = szary;
        setPixel(x + szerokosc/2, y, szary, szary, szary);
        numer++;
    }
  }
 SDL_UpdateWindowSurface(window);
}

void paletaMedianCutBW(){
  ileKubelkow = 0;
  ileKolorow = 0;
  czyscPalete();
  SDL_COLOR kolor;

  int szary = 0;
  int numer = 0;
  int indeks = 0;

  for(int y=0; y<wysokosc/2; y++){
     for(int x=0; x<szerokosc/2; x++){
        kolor = getPixel(x, y);
        szary = 0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b;
        obrazekS[numer] = szary;
        setPixel(x + szerokosc/2, y, szary, szary, szary);
        numer++;
    }
  }
 SDL_UpdateWindowSurface(window);
}

void czyscPalete(){
  for(int k=0; k<ileKolorow; k++)
      paleta8[k] = {0, 0, 0);
  ileKolorow = 0;
  for(int k=0; k<256; k++){
      paleta8s[k] = {0, 0, 0};
      paleta8k[k] = {0, 0, 0};
  }
}

