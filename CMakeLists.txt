cmake_minimum_required(VERSION 3.31)
project(GK_Projekt)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(GK_Projekt
        GK2025-Funkcje.cpp
        GK2025-Funkcje.h
        GK2025-MedianCut.cpp
        GK2025-MedianCut.h
        GK2025-Paleta.cpp
        GK2025-Paleta.h
        GK2025-Pliki.cpp
        GK2025-Pliki.h
        GK2025-Projekt.cpp
        GK2025-Zmienne.cpp
        GK2025-Zmienne.h)
