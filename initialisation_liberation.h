#ifndef ECE_CITY_3B_INITIALISATION_LIBERATION_H
#define ECE_CITY_3B_INITIALISATION_LIBERATION_H

#include "structure.h"

Jeu initialisation_jeu();
void liberation_jeu(Jeu* jeu);

Case** initialisation_map();
void liberation_map(Case*** map);

Route* initialisation_route();
void liberation_route(Route** route);

Batiment* initialisation_batiment();
void liberation_batiment(Batiment** batiment);

Maison* initialisation_maison();
void liberation_maison(Maison** maison);

#endif //ECE_CITY_3B_INITIALISATION_LIBERATION_H