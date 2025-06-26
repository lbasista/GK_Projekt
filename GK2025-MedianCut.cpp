// metody do algorytmu kwantyzacji (MedianCut)
#include "GK2025-MedianCut.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"
#include "GK2025-Paleta.h"

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

void MedianCutBW(int start, int koniec, int iteracja){
    for(int i = 0; i < iteracja; i++) std::cout << "  ";

    std::cout << "start: " << start << ", koniec: " << koniec << ", iteracja: " << iteracja << std::endl;

    if(iteracja > 0){

        sortujKubelekBW(start, koniec);
        for(int i = 0; i < iteracja; i++) std::cout << "  ";

        std::cout << "Dzielimy kubelek na poziomie " << iteracja << std::endl;

        int srodek = (start + koniec + 1) / 2;

        MedianCutBW(start, srodek - 1, iteracja - 1);
        MedianCutBW(srodek, koniec, iteracja - 1);
    } else {
        int sumaBW = 0;

        for (int p = start; p <= koniec; p++)
            sumaBW += obrazekS[p];

        Uint8 noweBW = sumaBW / (koniec + 1 - start);
        SDL_Color nowyKolor = { noweBW, noweBW, noweBW};
        paleta8s[ileKubelkow] = nowyKolor;

        std::cout << "Kubelek " << ileKubelkow << ": ";
        std::cout << "(s:" << start << ", k:" << koniec << ", e:" << (koniec + 1 - start) << ")";
        std::cout << std::endl;
        std::cout << "Kolor " << ileKubelkow << ": (" << (int)nowyKolor.r << ",";
        std::cout << (int)nowyKolor.g << "," << (int)nowyKolor.b << ")" << std::endl;
        ileKubelkow++;
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

    narysujPalete3b(0, 210, paleta8s);
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

void MedianCut(int start, int koniec, int iteracja){
    for(int i = 0; i < iteracja; i ++) std::cout << "  ";
    std::cout << "start: " << start << ", koniec: " << koniec << ", iteracja:" << iteracja << std::endl;
    if(iteracja > 0){
        Uint8 sortowanie = najwiekszaRoznica(start, koniec);
        switch(sortowanie){
            case 1: std::cout << "sortujemy wedlug R" << std::endl;
                    break;
            case 2: std::cout << "sortujemy wedlug G" << std::endl;
                    break;
            case 3: std::cout << "sortujemy wedlug B" << std::endl;
                    break;
        }

        sortujKubelek(start, koniec, sortowanie);

        for (int i = 0; i < iteracja; i++) std::cout << "  ";
        std::cout << "Dzielimy kubelek na poziomie " << iteracja << std::endl;

        int srodek = (start + koniec + 1) / 2;

        MedianCut(start, srodek - 1, iteracja - 1);
        MedianCut(srodek, koniec, iteracja - 1);
    } else {
        int sumaR = 0, sumaG = 0, sumaB =0;
        for(int p = start; p <= koniec; p++){
            sumaR += obrazekK[p].r;
            sumaG += obrazekK[p].g;
            sumaB += obrazekK[p].b;
        }

        int sredniaR = sumaR / (koniec + 1 - start);
        int sredniaG = sumaG / (koniec + 1 - start);
        int sredniaB = sumaB / (koniec + 1 - start);

        SDL_Color nowyKolor = {sredniaR, sredniaG, sredniaB};
        paleta8k[ileKubelkow] = nowyKolor;

        for (int p = start; p <= koniec; p++)
            obrazekK[p] = nowyKolor;

        std::cout << "Kubelek " << ileKubelkow << ": ";
        std::cout << "(s: " << start << ", k:" << koniec << ", e:" << (koniec + 1 - start) << ")";
        std::cout << std::endl;
        std::cout << "Kolor " << ileKubelkow << ": (" << (int)nowyKolor.r << ",";
        std::cout << (int)nowyKolor.g << "," << (int)nowyKolor.b << ")" << std::endl;
        ileKubelkow++;
    }
}
