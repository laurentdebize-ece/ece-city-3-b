cmake_minimum_required(VERSION 3.20.2)
project(ECE_CITY_3B C)

set(CMAKE_C_STANDARD 11)

add_executable(ECE_CITY_3B
        main.c structure.h
        liste.h liste.c
        construction_destruction.h construction_destruction.c
        initialisation_liberation.h initialisation_liberation.c
        affichage.h affichage.c compteur.c compteur.h
        debug.h debug.c jeu.c jeu.h fichier.h fichier.c)

add_subdirectory(raylib)
target_link_libraries(ECE_CITY_3B raylib)