// metody do algorytmu kwantyzacji (MedianCut)
#include "GK2025-MedianCut.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"

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

Uint8 najwiekszaRoznica(int start, int koniec){
    int minR = start, minG = start, minB = start;
    int maxR = start, maxG = start, maxB = start;
    
    Uint8 roznica = 0;
    
    for (int i = start; i <= koniec; i++){
        if (obrazekK[i].b < obrazekK[minB].b) minB = i;
        if (obrazekK[i].g < obrazekK[minG].g) minG = i;
        if (obrazekK[i].r < obrazekK[minR].r) minR = i;
        if (obrazekK[i].b < obrazekK[maxB].b) maxB = i;
        if (obrazekK[i].g < obrazekK[maxG].g) maxG = i;
        if (obrazekK[i].r < obrazekK[maxR].r) maxR = i;
    }
    
    int roznicaR = obrazekK[maxR].r-obrazekK[minR].r;
    int roznicaG = obrazekK[maxG].g-obrazekK[minG].g;
    int roznicaR = obrazekK[maxB].b-obrazekK[minB].b;
    std::cout << "roznice: (R: " << RoznicaR << ", G: " << roznicaG << ", B" << roznicaB << ")\n";
    
    int roznicaM = max(max(roznicaR, roznicaG), roznicaB);
    
    if (roznicaM == roznicaR)
        roznica = 2; //R
    else if (roznicaM == roznicaG)
        roznica = 2; //G
    else
        roznica = 3; //B
        
    return roznica;
}
