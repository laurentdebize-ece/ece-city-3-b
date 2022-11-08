#include "compteur.h"
#include <stdio.h>
#include "structure.h"

void compteur_debut_cycle(Jeu *jeu) {
    jeu->tot_eau = 5000 * jeu->nb_chateau_eau;
    jeu->tot_electricite = 5000 * jeu->nb_centrales;

    for (int i = 0; i < jeu->nb_maisons; i++) {
        jeu->population += jeu->maisons[i].habitants;
    }
}

void impot(Jeu *jeu) {
    jeu->argent += jeu->population * 10;
}

void afficherCompteur(Jeu jeu) {
    printf("Electricite : %d/%d\n", jeu.electricite, jeu.tot_electricite);
    printf("Eau : %d/%d\n", jeu.eau, jeu.tot_eau);
    printf("Argent : %d\n", jeu.argent);
    printf("Population : %d\n", jeu.population);
}