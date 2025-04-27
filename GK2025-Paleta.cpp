// funkcje do redukcji kolorów i tworzenia palet
#include "GK2025-Paleta.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"


void narzuconaV1(){
    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
    int nowyR, nowyG, nowyB;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = R>>6;
            nowyG = G>>6;
            nowyB = B>>7;

            R = nowyR<<6;
            G = nowyG<<6;
            B = nowyB<<7;

            setPixel(x + szerokosc/2, y, R, G, B);
        }

    }
}

void narzuconaV2(){
    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
        int nowyR, nowyG, nowyB;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = R>>6;
            nowyG = G>>6;
            nowyB = B>>7;

            R = nowyR*255.0/3.0;
            G = nowyG*255.0/3.0;
            B = nowyB*255.0;

            setPixel(x, y + wysokosc/2, R, G, B);
        }

    }

}

void narzuconaV3(){
    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
        int nowyR, nowyG, nowyB;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = round(R*4.0/31.0);
            nowyG = round(G*4.0/31.0);
            nowyB = round(B*1.0/31.0);


            R = nowyR*31.0/4.0;
            G = nowyG*31.0/4.0;
            B = nowyB*31.0/1.0;


            setPixel(x + szerokosc/2, y + wysokosc/2, R, G, B);
        }

    }
        SDL_UpdateWindowSurface(window);
}

void narzuconaV4(){
    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
    int nowyR, nowyG, nowyB;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;



            nowyR = R>>6;
            nowyG = G>>6;
            nowyB = B>>7;

            R = nowyR<<6;
            G = nowyG<<6;
            B = nowyB<<7;

            setPixel(x + szerokosc/2, y, R, G, B);
        }

    }
}


Uint8 z24Kdo8K(SDL_Color kolor){
    Uint8 kolor8bit;
    int R, G, B;
    int nowyR, nowyG, nowyB;

    R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = round(R*7.0/255.0);
            nowyG = round(G*7.0/255.0);
            nowyB = round(B*3.0/255.0);



    kolor8bit = (nowyR<<5) | (nowyG<<2) | nowyB;





    return kolor8bit;
}

SDL_Color z8Kdo24K(Uint8 kolor8bit){

  SDL_Color kolor;
  int R, G, B;
  int nowyR, nowyG, nowyB;

  nowyR = (kolor8bit&(0b11100000))>>5;
  nowyG = (kolor8bit&(0b00011100))>>2;
  nowyB = (kolor8bit&(0b00000011));


    R = nowyR*255.0/7.0;
    G = nowyG*255.0/7.0;
    B = nowyB*255.0/3.0;

    kolor.r = R;
    kolor.g = G;
    kolor.b = B;

    return kolor;
}


void narysujPalete(int px, int py, SDL_Color pal8[]) {
    int x, y;
    for (int k = 0; k < 32; k++) {
        x = k % 32;
        y = k / 32;
        for (int xx = 0; xx < 10; xx++) {
            for (int yy = 0; yy < 10; yy++) {
                setPixel(px + x * 10 + xx, py + y * 10 + yy, pal8[k].r, pal8[k].g, pal8[k].b);
            }
        }
    }
}
void paletaNarzucona() {
    Uint8 kolor8bit;
    SDL_Color kolor;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            kolor8bit = z24Kdo8K(kolor);
            SDL_Color zredukowanyKolor = z8Kdo24K(kolor8bit);
            setPixel(x + szerokosc / 2, y, zredukowanyKolor.r, zredukowanyKolor.g, zredukowanyKolor.b);
        }
    }

    for (int k = 0; k < 256; k++) {
        paleta8[k] = z8Kdo24K(k);
    }
    narysujPalete(0, wysokosc / 2, paleta8);

    SDL_UpdateWindowSurface(window);
}

bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2) {
    if (kolor1.r != kolor2.r)
        return false;
    if (kolor1.g != kolor2.g)
        return false;
    if (kolor1.b != kolor2.b)
        return false;
    return true;
}


int dodajKolor(SDL_Color kolor) {
    int aktualnyKolor = ileKolorow;
    paleta8[aktualnyKolor] = kolor;
    if (ileKolorow < 256) {
        cout<<"[";
        cout<<(int)aktualnyKolor<<": ";
        cout<<(int)kolor.r<<","<<(int)kolor.g<<","<<(int)kolor.b;
        cout<<"]"<<endl;
    }
    ileKolorow++;
    return aktualnyKolor;
}
int sprawdzKolor(SDL_Color kolor) {
    if (ileKolorow > 0) {
        for (int k=0; k<ileKolorow; k++) {
            if (porownajKolory(kolor, paleta8[k])) {
                return k;
            }
        }
    }
    return dodajKolor(kolor);
}
void czyscPalete() {
    for (int k=0; k<ileKolorow; k++)
        paleta8[k] = {0, 0, 0};

    ileKolorow = 0;
}


void paletaWykryta() {
    czyscPalete();
    int indexKoloru;
    SDL_Color kolor;
    for (int y=0; y<wysokosc/2; y++) {
        for (int x=0; x<szerokosc/2; x++) {
            kolor = getPixel(x, y);
            indexKoloru = sprawdzKolor(kolor);
        }
    }
    if (ileKolorow <= 256) {
    cout<<"Paleta spelnia ograniczenia 8-bit / piksel"<<endl;
    narysujPalete(0, 210, paleta8);
} else {
    cout<<"Paleta przekracza ograniczenia 8-bit / piksel"<<endl;
}
    cout<<endl<<"ile kolorow: "<<ileKolorow<<endl;
}

// Konwersja 24-bitowego RGB na 5-bitowy odcień szarości (0-31)
Uint8 z24Kdo5KS(SDL_Color kolor) {
    Uint8 szary = (kolor.r + kolor.g + kolor.b) / 3; // Średnia jasność
    return round(szary * 31.0 / 255.0); // Skalowanie do 5 bitów (0-31)
}

// Konwersja 5-bitowej szarości na 24-bitowy RGB
SDL_Color z5KSdo24K(Uint8 szary5bit) {
    SDL_Color kolor;
    Uint8 szary8bit = szary5bit * 255.0 / 31.0; // Skalowanie do 8 bitów
    kolor.r = szary8bit;
    kolor.g = szary8bit;
    kolor.b = szary8bit;
    return kolor;
}

void narzucona5KS() {
    SDL_Color kolor;
    Uint8 szary5bit;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            szary5bit = z24Kdo5KS(kolor); // Konwersja na 5-bitową szarość
            SDL_Color nowyKolor = z5KSdo24K(szary5bit); // Powrót do 24-bitów
            setPixel(x + szerokosc / 2, y, nowyKolor.r, nowyKolor.g, nowyKolor.b);
        }
    }
    SDL_UpdateWindowSurface(window);
}

void narysujPalete5KS(int px, int py, int rozmiarBloku) {
    for (int k = 0; k < 32; k++) {
        int x = px + (k % 16) * rozmiarBloku; // 16 kolumn, 2 rzędy (32/16=2)
        int y = py + (k / 16) * rozmiarBloku;
        SDL_Color kolor = z5KSdo24K(k); // Konwersja indeksu na kolor
        for (int i = 0; i < rozmiarBloku; i++) {
            for (int j = 0; j < rozmiarBloku; j++) {
                setPixel(x + i, y + j, kolor.r, kolor.g, kolor.b);
            }
        }
    }
}
