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

void odczytajPlik8(){
    SDL_Kolor kolor;
    Uint8 kolor8bit = 0;
    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    Uint8 ileBitow = 0;
    char identyfikator[] = "  ";

    std::cout << "Odczytujemy plik 'obraz8.bin' uzywajac metody read()" std::endl;

    ifstream wejscie("obraz8.bin", ios::binary);

    wejscie.read((chart*)&identyfikator, sizeof(char) + 2);
    wejscie.read((chart*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((chart*)&wysokoscObrazka, sizeof(Uint16);
    wejscie.read((chart*)&ileBitow, sizeof(Uint8));

    std::cout << "id: " << identyfikator << std::endl;
    std::cout << "szerokosc: " << szerokoscObrazka << std::endl;
    std::cout << "wysokosc: " << wysokoscObrazka << std::endl;
    std::cout << "ile bitow: " <<(int)ileBitow << std::endl;

    for (int y = 0; y < wysokoscObrazka; y++)
        for (int x = 0; x < szerokoscObrazka; x++){
            wejscie.read((char*)&kolor8bit, sizeof(Uint8));
            kolor = z8Kdo24K(kolor8bit);
            setPixel(x + (szerokosc / 2), y, kolor.r, kolor.g, kolor. b);
        }

    SDL_UpdateWindowSurface(window);
}
