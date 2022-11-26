#ifndef ECE_CITY_3B_AFFICHAGE_H
#define ECE_CITY_3B_AFFICHAGE_H

#include "structure.h"

#define ROUTE_NORD 0
#define ROUTE_SUD 1
#define ROUTE_EST 2
#define ROUTE_OUEST 3


void afficherCarte(Case** map);
void afficherMap(Jeu * jeu, int niveau);
void dessinerCases(Case cases[TAILLE_MAP_X][TAILLE_MAP_Y]);
void initCases(Case cases[TAILLE_MAP_X][TAILLE_MAP_Y]);
void affichageMapRaylib(Jeu* jeu);

void choixM(Jeu** jeu);
void menu1(Jeu* jeu);

#endif //ECE_CITY_3B_AFFICHAGE_H
