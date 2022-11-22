#ifndef ECE_CITY_3B_AFFICHAGE_H
#define ECE_CITY_3B_AFFICHAGE_H

#include "structure.h"

void afficherCarte(Case** map);
void afficherMap(Jeu * jeu, int niveau);
void dessinerCases(Case cases[LARGEUR_PLATEAU][LONGUEUR_PLATEAU]);
void initCases(Case cases[LARGEUR_PLATEAU][LONGUEUR_PLATEAU]);
void affichageMapRaylib();

#endif //ECE_CITY_3B_AFFICHAGE_H
