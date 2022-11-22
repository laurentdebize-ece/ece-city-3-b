#include "construction_destruction.h"
#include "initialisation_liberation.h"
#include "debug.h"
#include "affichage.h"
#include "eau.h"
#include <stdio.h>

int main() {
    printf("test SIMCITY !\n");

    Jeu jeu = initialisation_jeu();

    construire(&jeu,TYPE_ROUTE,0,1,0);
    construire(&jeu,TYPE_ROUTE,1,1,0);
    construire(&jeu,TYPE_MAISON,2,1,0);
    construire(&jeu,TYPE_ROUTE,4,4,0);
    construire(&jeu,TYPE_ROUTE,5,4,0);
    construire(&jeu,TYPE_CHATEAU_EAU,6,4,0);
    /*detruire(&jeu,TYPE_ROUTE,0,4,0);

    construire(&jeu,TYPE_MAISON,1,1,0);
    detruire(&jeu,TYPE_MAISON,0,0,0);

    construire(&jeu,TYPE_CENTRALE,4,1,0);
    detruire(&jeu,TYPE_CENTRALE,0,0,0);
    construire(&jeu,TYPE_CHATEAU_EAU,3,1,0);
    construire(&jeu,TYPE_CENTRALE,8,2,0);
*/
    if (jeu.nb_chateau_eau !=0 && jeu.nb_maisons != 0){
        printf("debut repartition\n");
        repartitionEau(&jeu);
        printf("repartition ok\n");
    }
    afficherCarte(jeu.map);
    printf("argent : %d\n",jeu.argent);

    liberation_jeu(&jeu);
    return 0;
}