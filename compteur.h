
#ifndef ECE_CITY_3B_COMPTEUR_H
#define ECE_CITY_3B_COMPTEUR_H

#include "structure.h"
#include "initialisation_liberation.h"

void maj_compteurs(Jeu *jeu);
void detection_temps(Jeu *jeu);
void compteur_electricite(Jeu* jeu);
void compteur_eau(Jeu* jeu);
void compteur_argent(Jeu* jeu);
void compteur_population(Jeu* jeu);
void impot(Jeu* jeu);
void calcul_eau(Jeu* jeu);
void calcul_elec(Jeu* jeu);
void afficherCompteur(Jeu jeu);

#endif //ECE_CITY_3B_COMPTEUR_H
