// funkcje do operacji na plikach
#include "GK2025-Funkcje.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Paleta.h"
#include "GK2025-MedianCut.h"
#include "GK2025-Pliki.h"


void zapiszPlikv0(){
    SDL_Color kolor;
    Uint16 szerokoscObrazka = szerokosc / 2;
    Uint16 wysokoscObrazka = wysokosc / 2;
    Uint8 ileBitow = 24;

    std::cout << "Zapisujemy plik 'obraz.bin' uzywajac operatora <<" << std::endl;
    ofstream wyjscie("obraz.bin");

    wyjscie << "DG";
    wyjscie << (Uint8)(szerokoscObrazka) << (Uint8)(szerokoscObrazka >> 8);
    wyjscie << (Uint8)(wysokoscObrazka) << (Uint8)(wysokoscObrazka >> 8);
    wyjscie << ileBitow;

    for(int y = 0; y < wysokoscObrazka; y++)
        for(int x = 0; x < szerokoscObrazka; x++){
            kolor = getPixel(x,y);
            wyjscie << kolor.r << kolor.g << kolor.b;
            }

    wyjscie.close();

    SDL_UpdateWindowSurface(window);
}
