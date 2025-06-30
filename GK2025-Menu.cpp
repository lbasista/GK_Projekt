// w pliku GK2025-Funkcje.cpp lub nowym pliku GK2025-Menu.cpp
#include "GK2025-Funkcje.h"
#include "GK2025-Pliki.h"
#include "GK2025-Paleta.h"
#include "GK2025-Zmienne.h"
#include "GK2025-MedianCut.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

// helper do pokazania prostego MessageBoxa
static bool showSDLMenu(const char* title,
                        const char* message,
                        const SDL_MessageBoxButtonData* buttons,
                        int buttonCount,
                        int& outClickedId)
{
    // w takiej właśnie kolejności: flags, window, title, message, numbuttons, buttons, colorScheme
    SDL_MessageBoxData mbd = {
        SDL_MESSAGEBOX_INFORMATION,
        window,
        title,
        message,
        buttonCount,
        buttons,
        nullptr
    };
    if (SDL_ShowMessageBox(&mbd, &outClickedId) < 0) {
        SDL_Log("SDL_ShowMessageBox error: %s", SDL_GetError());
        return false;
    }
    return true;
}

void handleMenu() {
    //  Main menu
    const SDL_MessageBoxButtonData mainBtns[] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Wczytaj BMP"     },
        { 0,                                      2, "BMP → DG-5"      },
        { 0,                                      3, "DG-5 → BMP"      },
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,4, "Anuluj"          }
    };
    int choice;
    if (!showSDLMenu("Menu główne", "Wybierz operację:", mainBtns, SDL_arraysize(mainBtns), choice))
        return;

    if (choice == 1) {
        // Wczytaj BMP
        string path;
        cout << "Ścieżka do BMP: ";
        getline(std::cin, path);
        ladujBMP(path.c_str(), 0, 0);
        SDL_UpdateWindowSurface(window);
        return;
    }
    if (choice == 3) {
        // DG-5 → BMP
        string path;
        cout << "Ścieżka do pliku DG-5: ";
        getline(cin, path);
        odczytajPlik5Bit(path.c_str());
        return;
    }

    if (choice != 2) {
        // Anuluj
        return;
    }

    //BMP → DG-5 → wybór trybu
    const SDL_MessageBoxButtonData modeBtns[] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 'a', "Paleta kolorowa NARZUCONA"    },
        { 0,                                      'b', "Odcienie szarości NARZUCONE" },
        { 0,                                      'c', "Paleta kolorowa DEDYKOWANA"  },
        { 0,                                      'd', "Odcienie szarości DEDYKOWANE" }
    };
    int mode;
    if (!showSDLMenu("Tryb konwersji", "Wybierz tryb:", modeBtns, SDL_arraysize(modeBtns), mode))
        return;

    // zapytaj o dithering
    const SDL_MessageBoxButtonData dithBtns[] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Tak" },
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Nie" }
    };
    int doDither;
    showSDLMenu("Dithering", "Czy zastosować dithering?", dithBtns, SDL_arraysize(dithBtns), doDither);

    // wykonaj wybraną konwersję
    switch(mode) {
      case 'a':
        if (doDither) narzucona5bColorDither();
        else          narzucona5bColor();
        break;
      case 'b':
        if (doDither) narzucona5bGrayDither();
        else          narzucona5KS();
        break;
      case 'c':
        if (doDither) paletaMedianCutColorFloyd();
        else          paletaDedykowana5b();
        break;
      case 'd':
        if (doDither) paletaMedianCutBWFloyd();
        else          paletaMedianCutBW();
        break;
      default:
        return;
    }
    SDL_UpdateWindowSurface(window);

    // zapisz wynik do DG-5
    std::string outPath;
    std::cout << "Nazwa pliku wyjściowego (DG-5): ";
    std::getline(std::cin, outPath);
    zapiszPlik5Bit(outPath.c_str());
}
