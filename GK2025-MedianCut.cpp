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

  MedianCutBW(0, numer-1, 3);

  for(int y=0; y<wysokosc/2; y++){
     for(int x=0; x<szerokosc/2; x++){
        szary = getPixel(x + szerokosc/2, y).r;
        indeks = znajdzSasiadaBW(szary);
        obrazekS[numer] = szary;
        setPixel(x + szerokosc/2, y + wysokosc/2, paleta8s[indeks].r, paleta8s[indeks].g, paleta8s[indeks].b);
    }
  }
 narysujPalete3b(0, 310, paleta8s);
 SDL_UpdateWindowSurface(window);
}

void paletaMedianCut(){
  ileKubelkow = 0;
  ileKolorow = 0;
  czyscPalete();
  SDL_COLOR kolor;
  
  int numer = 0;
  int indeks = 0;

  for(int y=0; y<wysokosc/2; y++){
     for(int x=0; x<szerokosc/2; x++){
        kolor = getPixel(x, y);
        obrazekK[numer] = {kolor.r, kolor.g, kolor.b};
        setPixel(x+szerokosc/2, y, obrazekK[numer].r, obrazekK[numer].g, obrazekK[numer].b);
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

