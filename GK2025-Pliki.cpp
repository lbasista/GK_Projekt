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
    //Uint8  ileBitow = 24;
    Uint8  ileBitow = 5; //Format r2g2b1

    char identyfikator[] = "DG";

    cout << "Zapisujemy plik 'obrazRGB.bin' uzywajac metody write()" << endl;
    ofstream wyjscie ("obrazRGB.bin", ios::binary);
    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&ileBitow, sizeof(Uint8));

    for (int y=0; y<wysokoscObrazka; y++) {
        for (int x=0; x<wysokoscObrazka; x++) {
            kolor = getPixel(x,y);
            //wyjscie.write((char*)&kolor, sizeof(Uint8)*3);

            //wyjscie.write((char*)&kolor.r, sizeof(Uint8));
            //wyjscie.write((char*)&kolor.g, sizeof(Uint8));
            //wyjscie.write((char*)&kolor.b, sizeof(Uint8));

            //Redukcja do r2g2b1
            Uint8 kolor5bit = ((kolor.r >> 6) << 4) | ((kolor.g >> 6) << 2) | (kolor.b >> 7);
            wyjscie.write((char*)&kolor5bit, sizeof(Uint8));
        }
    }
    wyjscie.close();
    SDL_UpdateWindowSurface(window);
}

void zapiszPlikv0(){
    SDL_Color kolor;
    Uint16 szerokoscObrazka = szerokosc / 2;
    Uint16 wysokoscObrazka = wysokosc / 2;
    //Uint8 ileBitow = 24;
    Uint8 ileBitow = 5;

    std::cout << "Zapisujemy plik 'obraz.bin' uzywajac operatora <<" << std::endl;
    ofstream wyjscie("obraz.bin");

    wyjscie << "DG";
    wyjscie << (Uint8)(szerokoscObrazka) << (Uint8)(szerokoscObrazka >> 8);
    wyjscie << (Uint8)(wysokoscObrazka) << (Uint8)(wysokoscObrazka >> 8);
    wyjscie << ileBitow;

    for(int y = 0; y < wysokoscObrazka; y++)
        for(int x = 0; x < szerokoscObrazka; x++){
            kolor = getPixel(x,y);
            //wyjscie << kolor.r << kolor.g << kolor.b;
            Uint8 kolor5bit = ((kolor.r >> 6) << 4) | ((kolor.g >> 6) << 2) | (kolor.b >> 7);
            wyjscie << kolor5bit;
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
            //wejscie.read((char*)&kolor, sizeof(Uint8)*3);
            Uint8 kolor5bit;
            wejscie.read((char*)&kolor5bit, sizeof(Uint8));

            //Odtwarzanie 24-bit z 5-bit
            Uint8 r2 = (kolor5bit >> 4) & 0x03;
            Uint8 g2 = (kolor5bit >> 2) & 0x03;
            Uint8 b1 = kolor5bit & 0x01;

            kolor.r = r2 * 85; //0, 85, 170, 255
            kolor.g = g2 * 85;
            kolor.b = b1 * 255;

            setPixel(x + (szerokosc / 2), y, kolor.r, kolor.g, kolor.b);
        }
    }
    SDL_UpdateWindowSurface(window);
}


void odczytajPlik8(){
    SDL_Color kolor;
    Uint8 kolor8bit = 0;
    Uint16 szerokoscObrazka = 0;
    Uint16 wysokoscObrazka = 0;
    Uint8 ileBitow = 0;
    char identyfikator[] = "  ";

    std::cout << "Odczytujemy plik 'obraz8.bin' uzywajac metody read()" << std::endl;

    ifstream wejscie("obraz8.bin", ios::binary);

    wejscie.read((char*)&identyfikator, sizeof(char) + 2);
    wejscie.read((char*)&szerokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka, sizeof(Uint16));
    wejscie.read((char*)&ileBitow, sizeof(Uint8));

    std::cout << "id: " << identyfikator << std::endl;
    std::cout << "szerokosc: " << szerokoscObrazka << std::endl;
    std::cout << "wysokosc: " << wysokoscObrazka << std::endl;
    std::cout << "ile bitow: " <<(int)ileBitow << std::endl;

    for (int y = 0; y < wysokoscObrazka; y++)
        for (int x = 0; x < szerokoscObrazka; x++){
            wejscie.read((char*)&kolor8bit, sizeof(Uint8));
            kolor = z5KSdo24K(kolor8bit);
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
    char identyfikator[] = "DG";

    cout<<"Zapisujemy plik 'obraz8.bin' uzywajac metody write()"<<endl;
    ofstream wyjscie("obraz8.bin", std::ios_base::binary);
    wyjscie.write((char*)&identyfikator, sizeof(char)*2);
    wyjscie.write((char*)&szerokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka, sizeof(Uint16));
    wyjscie.write((char*)&ileBitow, sizeof(Uint8));

    for (int y=0; y<wysokoscObrazka; y++) {
        for (int x=0; x<szerokoscObrazka; x++) {
            kolor = getPixel(x, y);
            kolor8bit = z24Kdo5KS(kolor);
            wyjscie.write((char*)&kolor8bit, sizeof(Uint8));
        }
    }
    wyjscie.close();
    SDL_UpdateWindowSurface(window);
}

/*Specyfikacja formatu DG-5

Offset | Rozmiar | Znaczenie
––––––––––––––––––––––––––––––––––––––––––––––––––––
0      | 2B      | identyfikator ASCII: "DG"
2      | 2B      | szerokość obrazu (uint16, little-endian)
4      | 2B      | wysokość obrazu (uint16, little-endian)
6      | 1B      | liczba bitów/piksel (wartość 5)
7      |         | dane pikseli: jeden bajt na piksel,
                 | gdzie bity [4..3] = R₂, [2..1] = G₂, [0] = B₁,
                 | pozostałe bity w bajcie nieużywane
*/

void zapiszPlikDG5(const char* filename) {
    ofstream f(filename, ios::binary);
    Uint16 w = szerokosc/2, h = wysokosc/2;
    char id[2] = {'D','G'};
    Uint8 nbit = 5;
    f.write(id,2);
    f.write((char*)&w, sizeof(w));
    f.write((char*)&h, sizeof(h));
    f.write((char*)&nbit,1);

    for(int y=0; y<h; ++y){
        for(int x=0; x<w; ++x){
            SDL_Color c = getPixel(x,y);
            Uint8 pix = ((c.r>>6)<<3) | ((c.g>>6)<<1) | (c.b>>7);
            f.put((char)pix);
        }
    }
    f.close();
}

void odczytajPlikDG5(const char* filename) {
    ifstream f(filename, ios::binary);
    char id[2];
    Uint16 w,h;
    Uint8 nbit;
    f.read(id,2);
    f.read((char*)&w,sizeof(w));
    f.read((char*)&h,sizeof(h));
    f.read((char*)&nbit,1);

    for(int y=0; y<h; ++y){
        for(int x=0; x<w; ++x){
            Uint8 pix = (Uint8)f.get();
            Uint8 r2 = (pix>>3)&0x03;
            Uint8 g2 = (pix>>1)&0x03;
            Uint8 b1 =  pix    &0x01;
            SDL_Color c;
            c.r = r2 * 85;
            c.g = g2 * 85;
            c.b = b1 * 255;
            setPixel(x, y, c.r, c.g, c.b);
        }
    }
    SDL_UpdateWindowSurface(window);
}


void zapiszPlik5Bit(const char* filename) {
    ofstream f(filename, ios::binary);
    Uint16 w = szerokosc/2, h = wysokosc/2;
    char id[2] = {'D','G'};
    Uint8 nbit = 5;
    f.write(id,2);
    f.write((char*)&w, sizeof(w));
    f.write((char*)&h, sizeof(h));
    f.write((char*)&nbit,1);
    for(int y=0; y<h; ++y) {
        for(int x=0; x<w; x+=8) {
            Uint8 block[8];
            for(int i=0;i<8;++i){
                SDL_Color c = getPixel(x+i,y);
                block[i] = z24Kdo5C(c);
            }
            // bit–plane
            for(int b=0;b<5;++b){
                Uint8 byte = 0;
                for(int i=0;i<8;++i){
                    byte |= ((block[i]>>b)&1) << i;
                }
                f.put(byte);
            }
        }
    }
    f.close();
}

void odczytajPlik5Bit(const char* filename) {
    ifstream f(filename, ios::binary);
    char id[2];
    Uint16 w,h;
    Uint8 nbit;
    f.read(id,2);
    f.read((char*)&w,sizeof(w));
    f.read((char*)&h,sizeof(h));
    f.read((char*)&nbit,1);
    for(int y=0; y<h; ++y) {
        for(int x=0; x<w; x+=8) {
            Uint8 block[8] = {0};
            for(int b=0;b<5;++b){
                Uint8 plane = (Uint8)f.get();
                for(int i=0;i<8;++i){
                    block[i] |= ((plane>>i)&1) << b;
                }
            }
            for(int i=0;i<8;++i){
                SDL_Color c = z5Cdo24K(block[i]);
                setPixel(x+i, y, c.r,c.g,c.b);
            }
        }
    }
    SDL_UpdateWindowSurface(window);
}