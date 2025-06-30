// funkcje do redukcji kolor�w i tworzenia palet
#include "GK2025-Paleta.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"
#include "GK2025-MedianCut.h"

template<typename T>
T clamp(const T& v, const T& lo, const T& hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

// Stała 4×4 tablica Bayera
static const int bayer4x4[4][4] = {
    { 0,  8,  2, 10},
    {12,  4, 14,  6},
    { 3, 11,  1,  9},
    {15,  7, 13,  5}
};

void czyscPalete() {
       for(int k = 0; k < ileKolorow; k++)
        paleta8[k] = {0, 0, 0};

    ileKolorow = 0;

    for(int k = 0; k < 256; k++){
        paleta8s[k] = {0, 0, 0};
        paleta8k[k] = {0, 0, 0};
    }
}

void narysujPalete(int px, int py, SDL_Color paleta[]) {
    for (int k = 0; k < 256; k++) {
        int x = k % 32;
        int y = k / 32;

        for (int dx = 0; dx < 10; dx++) {
            for (int dy = 0; dy < 10; dy++) {
                setPixel(px + x * 10 + dx, py + y * 10 + dy,
                        paleta8[k].r, paleta8[k].g, paleta8[k].b);
            }
        }
    }
}

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

            nowyR = R>>5;
            nowyG = G>>5;
            nowyB = B>>6;

            R = nowyR<<5;
            G = nowyG<<5;
            B = nowyB<<6;

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

            nowyR = R>>5;
            nowyG = G>>5;
            nowyB = B>>6;

            R = nowyR*255.0/7.0;
            G = nowyG*255.0/7.0;
            B = nowyB*255.0/3.0;

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

            nowyR = round(R*7.0/255.0);
            nowyG = round(G*7.0/255.0);
            nowyB = round(B*3.0/255.0);


            R = nowyR*255.0/7.0;
            G = nowyG*255.0/7.0;
            B = nowyB*255.0/3.0;


            setPixel(x + szerokosc/2, y + wysokosc/2, R, G, B);
        }

    }
        SDL_UpdateWindowSurface(window);
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

void narysujPalete5KS(int px, int py, SDL_Color paleta[]) {
    const int rozmiarBloku = 10;
    for (int k = 0; k < 32; ++k) {
        int x = px + (k % 16) * rozmiarBloku;
        int y = py + (k / 16) * rozmiarBloku;
        SDL_Color c = paleta[k];
        for (int dx = 0; dx < rozmiarBloku; ++dx)
            for (int dy = 0; dy < rozmiarBloku; ++dy)
                setPixel(x+dx, y+dy, c.r, c.g, c.b);
    }
}

Uint8 z24Kdo5C(SDL_Color c) {
    Uint8 r2 = c.r >> 6;  // 0..3
    Uint8 g2 = c.g >> 6;  // 0..3
    Uint8 b1 = c.b >> 7;  // 0..1
    return (r2<<3)|(g2<<1)|b1;
}
// Zamiana 5-bit index → 24-bitowy kolor RGB
SDL_Color z5Cdo24K(Uint8 idx) {
    SDL_Color c;
    Uint8 r2 = (idx>>3)&0x03;
    Uint8 g2 = (idx>>1)&0x03;
    Uint8 b1 =  idx    &0x01;
    c.r = r2 * 85;   // 0,85,170,255
    c.g = g2 * 85;
    c.b = b1 * 255;  // 0 lub 255
    c.a = 255;
    return c;
}

// konwersja do wymuszonej palety 2-2-1
void narzucona5bColor() {
    // raster główny
    for(int y=0; y<wysokosc/2; ++y){
        for(int x=0; x<szerokosc/2; ++x){
            SDL_Color c = getPixel(x,y);
            Uint8 idx = z24Kdo5C(c);
            SDL_Color q = z5Cdo24K(idx);
            // przesunięcie: w prawo o szerokosc/2, górna połowa → y
            setPixel(x + szerokosc/2, y, q.r, q.g, q.b);
        }
    }
    // legenda 32 kolory 2-2-1 → też w top-right, poniżej rysunku
    for(int k=0;k<32;++k) paleta8k[k] = z5Cdo24K(k);
    narysujPalete5KS(szerokosc/2, /*py=*/wysokosc/2/2, paleta8k);
    SDL_UpdateWindowSurface(window);
}

//  „Dedykowana” paleta 32 kolory metodą MedianCut → wymuszenie 2-2-1
void paletaDedykowana5b() {
    int n=0;
    for(int y=0; y<wysokosc/2; ++y)
        for(int x=0; x<szerokosc/2; ++x)
            obrazekK[n++] = getPixel(x,y);
    ileKubelkow=0;
    MedianCut(0,n-1,5);               // 32 kubełki
    // wymuś 2-2-1 na paleta8k[0..31]
    for(int k=0;k<32;++k){
        SDL_Color c=paleta8k[k];
        Uint8 idx=z24Kdo5C(c);
        paleta8k[k]=z5Cdo24K(idx);
    }
    // kwantyzacja
    for(int y=0;y<wysokosc/2;++y)
        for(int x=0;x<szerokosc/2;++x){
            SDL_Color c=getPixel(x,y);
            int i=znajdzSasiada(c);
            SDL_Color q=paleta8k[i];
            setPixel(x + szerokosc/2,y, q.r,q.g,q.b);
        }

    // Zastosowanie palety do obrazka
    for (int y = 0; y < wysokosc/2; ++y) {
        for (int x = 0; x < szerokosc/2; ++x) {
            SDL_Color c = getPixel(x, y);
            int idx = znajdzSasiada(c);
            SDL_Color q = paleta8k[idx];
            setPixel(x + szerokosc/2, y, q.r, q.g, q.b);
        }
    }

    // Rysowanie legendy 32 kolorów 2-2-1 w górnej połowie prawej ćwiartki:
    const int rozmiarBloku = 10;
    // paleta8k już zawiera 32 kolory w 2-2-1
    int legendY = (wysokosc/2) - (2 * rozmiarBloku);
    narysujPalete5KS(szerokosc/2, legendY, paleta8k);

    SDL_UpdateWindowSurface(window);
}

void narzucona5bGray() {
  for(int y=0;y<wysokosc/2;++y)
    for(int x=0;x<szerokosc/2;++x){
      SDL_Color c=getPixel(x,y);
      Uint8 g=z24Kdo5KS(c);
      SDL_Color q=z5KSdo24K(g);
      setPixel(x, y + wysokosc/2, q.r,q.g,q.b);
    }
  // legendę odcieni:
  narysujPalete5KS(0, wysokosc/2, paleta8s /*>32 długość*/);
  SDL_UpdateWindowSurface(window);
}

//Grayscale + ordered dithering 4×4 → bottom-left
void narzucona5bGrayDither() {
    // Dithering w dolnej połowie lewej ćwiartki
    for (int y = 0; y < wysokosc/2; ++y) {
        for (int x = 0; x < szerokosc/2; ++x) {
            SDL_Color c = getPixel(x, y);
            float lum = (c.r + c.g + c.b) / 3.0f;
            float v   = lum * 31.0f / 255.0f;
            float t   = (bayer4x4[y & 3][x & 3] / 16.0f) - 0.5f;
            int idx   = clamp(int(floor(v + t + 0.5f)), 0, 31);
            SDL_Color q = z5KSdo24K((Uint8)idx);
            setPixel(x, y + wysokosc/2, q.r, q.g, q.b);
        }
    }

    // Rysowanie legendy szarości 32 poziomy
    const int rozmiarBloku = 10;
    SDL_Color grayPal[32];
    for (int k = 0; k < 32; ++k)
        grayPal[k] = z5KSdo24K(k);

    // umieszczamy legendę na samym dole lewej połowy
    int legendY = wysokosc - (2 * rozmiarBloku);
    narysujPalete5KS(0, legendY, grayPal);

    SDL_UpdateWindowSurface(window);
}

// Kolor + ordered dithering 4×4 → bottom-right
void narzucona5bColorDither() {
    for(int y=0; y<wysokosc/2; ++y){
        for(int x=0; x<szerokosc/2; ++x){
            SDL_Color c = getPixel(x,y);
            float t  = (bayer4x4[y&3][x&3]/16.0f) - 0.5f;
            float vr = c.r*3.0f/255.0f + t;
            float vg = c.g*3.0f/255.0f + t;
            float vb = c.b*1.0f/255.0f + t;
            int r2 = clamp(int(floor(vr+0.5f)),0,3);
            int g2 = clamp(int(floor(vg+0.5f)),0,3);
            int b1 = clamp(int(floor(vb+0.5f)),0,1);
            Uint8 idx = (r2<<3)|(g2<<1)|b1;
            SDL_Color q = z5Cdo24K(idx);
            // offset: prawo i dół
            setPixel(x + szerokosc/2, y + wysokosc/2, q.r, q.g, q.b);
        }
    }
    // legenda 32 kolory 2-2-1 pod rysunkiem
    for(int k=0;k<32;++k) paleta8k[k]=z5Cdo24K(k);
    narysujPalete5KS(/*px=*/szerokosc/2, /*py=*/wysokosc/2 + (wysokosc/2)/2, paleta8k);
    SDL_UpdateWindowSurface(window);
}