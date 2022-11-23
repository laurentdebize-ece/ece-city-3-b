#include "construction_destruction.h"
#include "initialisation_liberation.h"
#include "debug.h"
#include "affichage.h"
#include "compteur.h"
#include <stdio.h>
#include "jeu.h"

int main() {


    printf("test SIMCITY !\n");
    int niveauActuel=0;
    Jeu jeu = initialisation_jeu();
    bool end=false;
    affichageMapRaylib(&jeu);
    choix_mode_jeu(&jeu);
    while (end !=true) {
        // fonction pour commencer la partie et boucler tant que la partie n'est pas finie
        end = jouer(&jeu, &niveauActuel);
    }

    /*construire(&jeu,TYPE_ROUTE,0,0,0);
    construire(&jeu,TYPE_ROUTE,1,0,0);
    construire(&jeu,TYPE_ROUTE,2,0,0);
    construire(&jeu,TYPE_ROUTE,0,1,0);
    construire(&jeu,TYPE_ROUTE,0,2,0);
    construire(&jeu,TYPE_ROUTE,0,3,0);
    construire(&jeu,TYPE_ROUTE,0,4,0);
    construire(&jeu,TYPE_ROUTE,0,5,0);
    construire(&jeu,TYPE_ROUTE,0,6,0);
    construire(&jeu,TYPE_ROUTE,0,7,0);
    construire(&jeu,TYPE_ROUTE,0,8,0);
    construire(&jeu,TYPE_ROUTE,3,0,0);
    construire(&jeu,TYPE_ROUTE,4,0,0);
    detruire(&jeu,TYPE_ROUTE,0,4,0);

    construire(&jeu,TYPE_MAISON,1,7,0);
    //detruire(&jeu,TYPE_MAISON,0,0,0);

    construire(&jeu,TYPE_CENTRALE,4,1,0);
    detruire(&jeu,TYPE_CENTRALE,0,0,0);
    construire(&jeu,TYPE_CHATEAU_EAU,3,1,0);
    construire(&jeu,TYPE_CENTRALE,8,2,0);
    afficherCarte(jeu.map);
*/
    liberation_jeu(&jeu);
    return 0;
}