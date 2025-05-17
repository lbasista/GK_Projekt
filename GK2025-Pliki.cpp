// funkcje do operacji na plikach
#include "GK2025-Funkcje.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Paleta.h"
#include "GK2025-MedianCut.h"
#include "GK2025-Pliki.h"

void zapiszPlik(){
    SDL_Color kolor;
    Uint16 szerokoscObrazka = szerokosc / 2;
    Uint16 wysokoscObrazka = wysokosc / 2;
    Uint8  ileBitow = 24;

    char identyfikator[] = "DG";

    cout << "Zapisujemy plik 'obrazRGB.bin' uzywajac metody write()" << endl;
    ofstream wyjscie ('obrazRGB.bin', ios::binary);
    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&ileBitow, sizeof(Uint8));

    for (int y=0; y<wysokoscObrazka; y++) {
        for (int x=0; x<wysokoscObrazka; x++) {
            kolor = getPixel(x,y);
            wyjscie.write((char*)&kolor, sizeof(Uint8)*3);

            wyjscie.write((char*)&kolor.r, sizeof(Uint8));
            wyjscie.write((char*)&kolor.g, sizeof(Uint8));
            wyjscie.write((char*)&kolor.b, sizeof(Uint8));
        }
    }

    wyjscie.close();

    SDL_UpdateWindowSurface(window);

}

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
