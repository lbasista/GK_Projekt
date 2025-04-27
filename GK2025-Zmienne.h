// zmienne globalne
#ifndef GK2025_ZMIENNE_H_INCLUDED
#define GK2025_ZMIENNE_H_INCLUDED

#include <SDL2/SDL.h>

#define szerokosc 640
#define wysokosc 400

#define tytul "GK2025 - Projekt - Zespol XX"

extern SDL_Window* window;
extern SDL_Surface* screen;

extern SDL_Color paleta8[szerokosc*wysokosc];
extern int ileKolorow;

extern SDL_Color paleta8k[256];
extern SDL_Color paleta8s[256];

extern int ileKubelkow;
extern Uint8 obrazekS[320*200];
extern SDL_Color obrazel[320*200];

#endif // GK2025_ZMIENNE_H_INCLUDED
