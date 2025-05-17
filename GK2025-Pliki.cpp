// funkcje do operacji na plikach
#include "GK2025-Funkcje.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Paleta.h"
#include "GK2025-MedianCut.h"
#include "GK2025-Pliki.h"

void odczytajPlik() {
    SDL_Color kolor;
    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    Uint8 ileBitow = 0;
    char identyfikator[] = "  ";

    cout << "Odczytujemy plik 'obrazRGB.bin' uzywajac metody read()";
    ifstream wejscie("obrazRGB.bin", ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char)*2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&ileBitow, sizeof(Uint8));

    cout << "id: " << identyfikator << endl;
    cout << "szerokosc: " << wysokoscObrazka << endl;
    cout << "wysokosc: " << szerokoscObrazka << endl;
    cout << "ile bitow: " << ileBitow << endl;
    
    for (int y=0; y<wysokoscObrazka; y++) {
        for (int x=0; x<szerokoscObrazka; x++) {
            wejscie.read((char*)&kolor, sizeof(Uint8)*3);
            setPixel(x+(szerokosc/2), y, kolor.r, kolor.g, kolor.b);
        }
    }

    SDL_UpdateWindowSurface(window);
}
