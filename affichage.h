#ifndef ECE_CITY_3B_AFFICHAGE_H
#define ECE_CITY_3B_AFFICHAGE_H

#include "structure.h"

void afficherCarte(Case** map);
void afficherMap(Jeu * jeu, int niveau);
void dessinerCases(Case cases[TAILLE_MAP_X][TAILLE_MAP_Y]);
void initCases(Case cases[TAILLE_MAP_X][TAILLE_MAP_Y]);
void affichageMapRaylib(Jeu* jeu);

#endif //ECE_CITY_3B_AFFICHAGE_H
