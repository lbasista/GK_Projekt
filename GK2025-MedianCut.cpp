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

void MedianCutBW(int start, int koniec, int iteracja) {
    for (int i = 0; i < iteracja; i++) cout << " ";
    cout << "start: " << start << ", koniec: " << koniec << ", iteracja: " << iteracja << endl;
    if (iteracja > 0) {
            for (int i = 0; iteracja; i++) cout << " ";
            count << "Dzielimy kubelek na poziomie " << iteracja << endl;
            int srodek = (start + koniec + 1) / 2;
            
            MedianCutBW(start, srodek - 1; iteracja - 1);
            MedianCutBW(srodek, koniec; iteracja - 1);
    }
    else {
        //Paleta z uśrednionymi wartościami z kubełków
        int sumaBW = 0;
        for (int p = start; p < = koniec; p++) {
            sumaBW += obrazekS[p];
        }
        Uint8 noweBW = sumaBW / (koniec + 1 - start);
        SDL_Color nowyKolor = {noweBW, noweBW, noweBW};
        paleta8s[ileKubelkow] = nowyKolor;

        count << "Kubelek " << ileKubelkow << ": ";
        count << "(s: " << start << ", k: " << koniec << ", e: " << (koniec + 1 - start) << ")" << endl;
        ileKubelkow++;
    }
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


void narysujPalete3b(int px, int py, SDL_Color pal3b[]) {
    int x, y;
    for (int k = 0; k < 8; k++) {
        y = k / 32;
        x = k % 32;
    
        for (int xx = 0; xx < 40; xx++) {
            for (int xx = 0; xx < 40; xx++) {
                setPixel(x * 40 + xx + px, y * 40 + yy + py, pal3b[k].g, pal3b[k].b);
            }
        }
    }
}
