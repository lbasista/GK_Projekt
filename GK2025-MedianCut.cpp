// metody do algorytmu kwantyzacji (MedianCut)
#include "GK2025-MedianCut.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"
#include "GK2025-Paleta.h"

#include <iostream>
#include  <vector>
#include <array>

using namespace std;

Uint8 najwiekszaRoznica(int start, int koniec){
    int minR = start, minG = start, minB = start;
    int maxR = start, maxG = start, maxB = start;

    Uint8 roznica = 0;

    for(int i = start; i <= koniec; i++){
        if(obrazekK[i].b < obrazekK[minB].b) minB = i;
        if(obrazekK[i].g < obrazekK[minB].g) minG = i;
        if(obrazekK[i].r < obrazekK[minB].r) minR = i;
        if(obrazekK[i].b > obrazekK[minB].b) maxB = i;
        if(obrazekK[i].g > obrazekK[minB].g) maxG = i;
        if(obrazekK[i].r > obrazekK[minB].r) maxR = i;
    }

    int roznicaR = obrazekK[maxR].r - obrazekK[minR].r;
    int roznicaG = obrazekK[maxG].g - obrazekK[minG].g;
    int roznicaB = obrazekK[maxB].b - obrazekK[minB].b;

    std::cout << "roznice: (R:" << roznicaR << ", G:" << roznicaG << ", B:" << roznicaB << ")\n";

    int roznicaM = max(max(roznicaR, roznicaG), roznicaB);

    if(roznicaM == roznicaR)
        roznica = 1;
    else if(roznicaM == roznicaG)
        roznica = 2;
    else roznica = 3;
    return roznica;
}

int znajdzSasiadaBW(Uint8 wartosc){
    int minimum = 999;
    int indexMinimum = 0;
    int odleglosc = 0;

    for(int i = 0; i < ileKubelkow; i++){
        odleglosc = abs(wartosc - paleta8s[i].r);
        if(odleglosc < minimum){
            minimum = odleglosc;
            indexMinimum = i;
        }
    }
    return indexMinimum;
}


int znajdzSasiada(SDL_Color kolor){
    int minimum = 999999;
    int indexMinimum;

    SDL_Color kolorPaleta;
    float odleglosc;

    for(int i = 0; i < 256; i++){
        kolorPaleta = paleta8k[i];
        odleglosc = sqrt((kolor.r - kolorPaleta.r) * (kolor.r - kolorPaleta.r) +
                         (kolor.g - kolorPaleta.g) * (kolor.g - kolorPaleta.g) +
                         (kolor.b - kolorPaleta.b) * (kolor.b - kolorPaleta.b));
        if(odleglosc < minimum){
            minimum = odleglosc;
            indexMinimum = i;
        }
    }
    return indexMinimum;
}

void sortujKubelekBW(int start, int koniec){
    int minimum;

    for(int p = start; p <= koniec; p++){

        minimum = p;
        for(int i = p; i <= koniec; i ++){
            if(obrazekS[i] < obrazekS[minimum])
                minimum = i;
        }
        swap(obrazekS[p], obrazekS[minimum]);
    }
}

void sortujKubelek(int start, int koniec, Uint8 sortowanie){
    int minimum;
    for(int p = start; p <= koniec; p++){
        minimum = p;
        for(int i = p; i <= koniec; i++){
            switch(sortowanie){
                case 1:
                    if(obrazekK[i].r < obrazekK[minimum].r) minimum = i;
                    break;
                case 2:
                    if(obrazekK[i].g < obrazekK[minimum].g) minimum = i;
                    break;
                case 3:
                    if(obrazekK[i].b < obrazekK[minimum].b) minimum = i;
                    break;
            }
        }
        swap(obrazekK[p],obrazekK[minimum]);
    }
}

void MedianCutBW(int start, int koniec, int iteracja) {
    if (iteracja > 0) {
        sortujKubelekBW(start, koniec);
        int srodek = (start + koniec + 1) / 2;
        MedianCutBW(start,     srodek - 1, iteracja - 1);
        MedianCutBW(srodek,    koniec,     iteracja - 1);
    } else {
        // Obliczamy średnią jasność w kubełku
        int suma = 0;
        for (int i = start; i <= koniec; ++i)
            suma += obrazekS[i];
        Uint8 noweBW = Uint8(suma / (koniec + 1 - start));

        // ręczne przypisanie każdej składowej SDL_Color
        SDL_Color nowyKolor;
        nowyKolor.r = noweBW;
        nowyKolor.g = noweBW;
        nowyKolor.b = noweBW;
        nowyKolor.a = 255;

        paleta8s[ileKubelkow++] = nowyKolor;
    }
}

void MedianCut(int start, int koniec, int iteracja) {
    if (iteracja > 0) {
        Uint8 sortowanie = najwiekszaRoznica(start, koniec);
        sortujKubelek(start, koniec, sortowanie);
        int srodek = (start + koniec + 1) / 2;
        MedianCut(start,    srodek - 1, iteracja - 1);
        MedianCut(srodek,   koniec,     iteracja - 1);
    } else {
        // Obliczamy średnie R/G/B w kubełku
        int sumaR = 0, sumaG = 0, sumaB = 0;
        for (int i = start; i <= koniec; ++i) {
            sumaR += obrazekK[i].r;
            sumaG += obrazekK[i].g;
            sumaB += obrazekK[i].b;
        }
        int count = koniec + 1 - start;
        Uint8 sredniaR = Uint8(sumaR / count);
        Uint8 sredniaG = Uint8(sumaG / count);
        Uint8 sredniaB = Uint8(sumaB / count);

        // ręczne przypisanie każdej składowej SDL_Color
        SDL_Color nowyKolor;
        nowyKolor.r = sredniaR;
        nowyKolor.g = sredniaG;
        nowyKolor.b = sredniaB;
        nowyKolor.a = 255;

        paleta8k[ileKubelkow++] = nowyKolor;

        // (opcjonalnie) nadpisanie obrazekK[p] na nowyKolor, jeśli potrzebne
        for (int p = start; p <= koniec; ++p)
            obrazekK[p] = nowyKolor;
    }
}

void paletaMedianCutBW() {
    ileKubelkow = 0;
    ileKolorow = 0;
    czyscPalete();
    SDL_Color kolor;
    int szary = 0;
    int numer = 0;
    int indeks = 0;

    for (int y = 0; y < wysokosc / 2; y++)
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            szary = 0.299 * kolor.r + 0.587 * kolor.g + 0.114 * kolor.b;
            obrazekS[numer] = szary;
            setPixel(x + szerokosc / 2, y, szary, szary, szary);
            numer++;
        }

    MedianCutBW(0, numer - 1, 5);

    for (int y = 0; y < wysokosc / 2; y++)
        for (int x = 0; x < szerokosc / 2; x++){
            szary = getPixel(x + szerokosc / 2, y).r;
            indeks = znajdzSasiadaBW(szary);
            setPixel(x + szerokosc / 2, y + wysokosc / 2,
                     paleta8s[indeks].r, paleta8s[indeks].g, paleta8s[indeks].b);
        }

    narysujPalete5KS(0, 210, paleta8s);
    SDL_UpdateWindowSurface(window);
}

void paletaMedianCut() {
    ileKubelkow = 0;
    ileKolorow = 0;
    czyscPalete();
    SDL_Color kolor;
    int numer = 0;
    int indeks = 0;

    for (int y = 0; y < wysokosc / 2; y++)
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            obrazekK[numer] = {kolor.r, kolor.g, kolor.b};
            setPixel(x + szerokosc / 2, y,
                     obrazekK[numer].r, obrazekK[numer].g, obrazekK[numer].b);
            numer++;
        }

    MedianCut(0, numer - 1, 5);

    for (int y = 0; y < wysokosc / 2; y++)
        for (int x = 0; x < szerokosc / 2; x++){
            kolor = getPixel(x, y);
            indeks = znajdzSasiada(kolor);
            setPixel(x + szerokosc / 2, y + wysokosc / 2,
                        paleta8k[indeks].r, paleta8k[indeks].g, paleta8k[indeks].b);
        }

    narysujPalete(0, 210, paleta8k);
    SDL_UpdateWindowSurface(window);
}

// MedianCutBW + Floyd–Steinberg → paleta BW 32 poziomy
void paletaMedianCutBWFloyd() {
    int w = szerokosc/2, h = wysokosc/2;
    vector<vector<float>> buf(h, vector<float>(w));
    for(int y=0; y<h; ++y)
        for(int x=0; x<w; ++x)
            buf[y][x] = 0.299f*getPixel(x,y).r
                      + 0.587f*getPixel(x,y).g
                      + 0.114f*getPixel(x,y).b;

    // przygotowanie palety BW
    ileKubelkow = ileKolorow = 0;
    czyscPalete();
    int n = w*h;
    for(int i=0; i<n; ++i) obrazekS[i] = Uint8(buf[i/w][i%w]);
    MedianCutBW(0, n-1, 5);
    // wymuszenie 5-bitowego zakresu
    for(int k=0; k<ileKubelkow; ++k) {
        Uint8 idx5 = z24Kdo5KS(paleta8s[k]);
        paleta8s[k] = z5KSdo24K(idx5);
    }

    // Floyd–Steinberg
    for(int y=0; y<h; ++y) {
        for(int x=0; x<w; ++x) {
            float old = buf[y][x];
            int best = 0; float md = fabsf(old - paleta8s[0].r);
            for(int k=1; k<ileKubelkow; ++k) {
                float d = fabsf(old - paleta8s[k].r);
                if(d < md) { md = d; best = k; }
            }
            float neu = paleta8s[best].r;
            SDL_Color q = paleta8s[best];
            setPixel(x, y + h, q.r, q.g, q.b);
            float err = old - neu;
            if(x+1 < w)           buf[y][x+1]   += err * 7.0f/16.0f;
            if(x-1 >= 0 && y+1<h) buf[y+1][x-1] += err * 3.0f/16.0f;
            if(y+1 < h)           buf[y+1][x]   += err * 5.0f/16.0f;
            if(x+1<w && y+1<h)    buf[y+1][x+1] += err * 1.0f/16.0f;
        }
    }

    // legenda 32 odcieni tuż poniżej ditheringu
    narysujPalete5KS(0, h +10, paleta8s);
    SDL_UpdateWindowSurface(window);
}

// MedianCut (RGB) + Floyd–Steinberg → paleta kolorowa 2-2-1
void paletaMedianCutColorFloyd() {
    int w = szerokosc/2, h = wysokosc/2;
    vector<vector<array<float,3>>> buf(h, vector<array<float,3>>(w));
    for(int y=0; y<h; ++y)
        for(int x=0; x<w; ++x) {
            SDL_Color c = getPixel(x,y);
            buf[y][x] = { float(c.r), float(c.g), float(c.b) };
        }

    // przygotowanie palety kolorowej
    ileKubelkow = ileKolorow = 0;
    czyscPalete();
    int n = w*h;
    for(int i=0; i<n; ++i) obrazekK[i] = getPixel(i % w, i / w);
    MedianCut(0, n-1, 5);
    // wymuszenie 2-2-1 bitów
    for(int k=0; k<ileKubelkow; ++k) {
        Uint8 idx5 = z24Kdo5C(paleta8k[k]);
        paleta8k[k] = z5Cdo24K(idx5);
    }

    // Floyd–Steinberg
    for(int y=0; y<h; ++y) {
        for(int x=0; x<w; ++x) {
            auto old = buf[y][x];
            int best = 0; float md = 1e12f;
            for(int k=0; k<ileKubelkow; ++k) {
                SDL_Color p = paleta8k[k];
                float dr = old[0]-p.r, dg = old[1]-p.g, db = old[2]-p.b;
                float d2 = dr*dr + dg*dg + db*db;
                if(d2 < md) { md = d2; best = k; }
            }
            SDL_Color q = paleta8k[best];
            // <-- przesunięcie: prawo o w, dół o h
            setPixel(x + w, y + h, q.r, q.g, q.b);
            float errR = old[0] - q.r;
            float errG = old[1] - q.g;
            float errB = old[2] - q.b;
            if(x+1 < w) {
                buf[y][x+1][0] += errR * 7.0f/16.0f;
                buf[y][x+1][1] += errG * 7.0f/16.0f;
                buf[y][x+1][2] += errB * 7.0f/16.0f;
            }
            if(x-1>=0 && y+1<h) {
                buf[y+1][x-1][0] += errR * 3.0f/16.0f;
                buf[y+1][x-1][1] += errG * 3.0f/16.0f;
                buf[y+1][x-1][2] += errB * 3.0f/16.0f;
            }
            if(y+1 < h) {
                buf[y+1][x][0]   += errR * 5.0f/16.0f;
                buf[y+1][x][1]   += errG * 5.0f/16.0f;
                buf[y+1][x][2]   += errB * 5.0f/16.0f;
            }
            if(x+1<w && y+1<h) {
                buf[y+1][x+1][0] += errR * 1.0f/16.0f;
                buf[y+1][x+1][1] += errG * 1.0f/16.0f;
                buf[y+1][x+1][2] += errB * 1.0f/16.0f;
            }
        }
    }

    // legenda 32 kolorów
    narysujPalete5KS(w, h +10, paleta8k);
    SDL_UpdateWindowSurface(window);
}