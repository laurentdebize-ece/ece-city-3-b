#include "compteur.h"
#include <stdio.h>
#include "structure.h"
#include "eau.h"
#include "elec.h"

void maj_compteurs(Jeu *jeu) {
    jeu->tot_eau = 5000 * jeu->nb_chateau_eau;
    jeu->tot_electricite = 5000 * jeu->nb_centrales;
    compteur_population(jeu);
    calcul_eau(jeu);
    calcul_elec(jeu);
}

void impot(Jeu *jeu) {
    jeu->argent += jeu->population * 10;
}

void calcul_eau(Jeu* jeu){
    jeu->eau = jeu->tot_eau - jeu->population;

}

void calcul_elec(Jeu* jeu){
    jeu->electricite = jeu->tot_electricite - jeu->population;
}

void compteur_population(Jeu* jeu){
    jeu->population = 0;
    if(jeu->nb_maisons != 0){
        for(int i = 0; i < jeu->nb_maisons; i++){
            jeu->population += jeu->maisons[i].habitants;
        }
    }
}

void afficherCompteur(Jeu jeu) {
    printf("\n");
    printf("Electricite : %d/%d         ", jeu.electricite, jeu.tot_electricite);
    printf("Eau : %d/%d         ", jeu.eau, jeu.tot_eau);
    printf("Argent : %d         ", jeu.argent);
    printf("Population : %d\n", jeu.population);
    printf("\n");
}