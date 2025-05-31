// funkcje do redukcji kolorów i tworzenia palet
#include "GK2025-Paleta.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"
#include "GK2025-MedianCut.h"

void czyscPalete() {
       for(int k = 0; k < ileKolorow; k++)
        paleta8[k] = {0, 0, 0};

    ileKolorow = 0;

    for(int k = 0; k < 256; k++){
        paleta8s[k] = {0, 0, 0};
        paleta8k[k] = {0, 0, 0};
    }
}

void narysujPalete3b(int px, int py, SDL_Color pal3b[]) {
    int x, y;
    for (int k = 0; k < ileKubelkow; k++) {
        x = k % 8;
        y = k / 8;

        for (int xx = 0; xx < 20; xx++) {
            for (int yy = 0; yy < 20; yy++) {
                setPixel(x * 20 + xx + px, y * 20 + yy + py,
                         pal3b[k].r, pal3b[k].g, pal3b[k].b);
            }
        }
    }
}


void narysujPalete(int px, int py, SDL_Color paleta[]) {
    for (int k = 0; k < 32; k++) {
        int x = k % 8;
        int y = k / 8;

        for (int dx = 0; dx < 20; dx++) {
            for (int dy = 0; dy < 20; dy++) {
                setPixel(px + x * 20 + dx, py + y * 20 + dy,
                        paleta[k].r, paleta[k].g, paleta[k].b);
            }
        }
    }
}
