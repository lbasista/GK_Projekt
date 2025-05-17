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

void zapiszPlik8() {
    SDL_Color kolor;
    Uint8 kolor8bit;
    Uint16 szerokoscObrazka = szerokosc/2;
    Uint16 wysokoscObrazka = wysokosc/2;
    Uint8 ileBitow = 8;
    char identyfikator[] = "DG"

    cout<<"Zapisujemy plik 'obraz8.bin' uzywajac metody write()"<<endl;
    ofstream wyjscie("obraz8.bin", ios:binary);
    wyjscie.write((char*)&identyfikator, sizeof());
    wyjscie.write((char*)&szerokoscObrazka, sizeof());
    wyjscie.write((char*)&wysokoscObrazka, sizeof());
    wyjscie.write((char*)&ileBitow, sizeof());

    for (int y=0; y<wysokoscObrazka; y++) {
        for (int x=0; x<szerokoscObrazka; x++) {
            kolor = getPixel(x, y);
            kolor8bit = z24Kdo8K(kolor);
            wyjscie.write((char*)&kolor8bit, sizeof(Uint8));
        }
    }
    wyjscie.close();
    SDL_UpdateWindowSurface(window);
}
