#include "construction_destruction.h"
#include "initialisation_liberation.h"
#include "debug.h"
#include "affichage.h"
#include "compteur.h"
#include <stdio.h>

int main() {
    printf("test SIMCITY !\n");

    Jeu jeu = initialisation_jeu();

    compteur_debut_cycle(&jeu);
    construire(&jeu,TYPE_ROUTE,0,0,0);
    construire(&jeu,TYPE_ROUTE,1,0,0);
    construire(&jeu,TYPE_ROUTE,2,0,0);
    construire(&jeu,TYPE_ROUTE,0,1,0);
    construire(&jeu,TYPE_ROUTE,3,0,0);
    construire(&jeu,TYPE_ROUTE,4,0,0);
    detruire(&jeu,TYPE_ROUTE,0,4,0);

    construire(&jeu,TYPE_MAISON,1,1,0);
    detruire(&jeu,TYPE_MAISON,0,0,0);

    construire(&jeu,TYPE_CENTRALE,4,1,0);
    detruire(&jeu,TYPE_CENTRALE,0,0,0);
    construire(&jeu,TYPE_CHATEAU_EAU,3,1,0);
    construire(&jeu,TYPE_CENTRALE,8,2,0);

    afficherCarte(jeu.map);
    afficherCompteur(jeu);
    liberation_jeu(&jeu);
    return 0;
}