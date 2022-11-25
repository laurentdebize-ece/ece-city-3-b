#include "construction_destruction.h"
#include "initialisation_liberation.h"
#include "debug.h"
#include "affichage.h"
#include "compteur.h"
#include <stdio.h>
#include "jeu.h"
#include"eau.h"
#include"elec.h"

int main() {

    printf("test SIMCITY !\n");
    int niveauActuel=0;
    Jeu jeu = initialisation_jeu();
    bool end=false;
    affichageMapRaylib(&jeu);
    choix_mode_jeu(&jeu);
    while (end !=true) {
         //fonction pour commencer la partie et boucler tant que la partie n'est pas finie
        end = jouer(&jeu, &niveauActuel);
    }
/*
    for(int i=0;i<TAILLE_MAP_X;i++){
        construire(&jeu,TYPE_ROUTE,i,0,0);
    }
    for(int i=0;i<TAILLE_MAP_Y;i++){
        construire(&jeu,TYPE_ROUTE,0,i,0);
    }
    for(int i=0;i<10;i++){
        construire(&jeu,TYPE_MAISON,i*3 + 1,1,0);

        jeu.maisons[i].niveau = NIVEAU_GRATTE_CIEL;
    }
    for(int i=0;i<2;i++){
        construire(&jeu,TYPE_CENTRALE,1,(i+1)*4,1);
    }
    for(int i=0;i<2;i++){
        construire(&jeu,TYPE_CHATEAU_EAU,1,(i+6)*4,1);
    }

    if(!detruire(&jeu,3,24))
        printf("erreur destruction\n");

    afficherCarte(jeu.map);

    
    repartitionEau(&jeu);
    repartition_electricite(&jeu);
    repartition_habitants(&jeu);

    int totalHabitants = 0;
    int totalEau = 0;
    int totalElec = 0;

    for (int i = 0; i < jeu.nb_maisons; i++) {
        totalHabitants += jeu.maisons[i].habitants;
        totalEau += jeu.maisons[i].eau;
        totalElec += jeu.maisons[i].electricite;
    }
    DEBUG_PRINT_INT(totalHabitants);
    DEBUG_PRINT_INT(totalEau);
    DEBUG_PRINT_INT(totalElec);
    DEBUG_PRINT("\n")
*/
    liberation_jeu(&jeu);
    return 0;
}