#include "compteur.h"
#include <stdio.h>
#include "structure.h"

void compteur_debut_cycle(Jeu *jeu) {
    jeu->tot_eau = 5000 * jeu->nb_chateau_eau;
    jeu->tot_electricite = 5000 * jeu->nb_centrales;
    compteur_population(jeu);
    calcul_eau(jeu);
    calcul_elec(jeu);
    impot(jeu);

}

void compteur_cycle_maison(Jeu *jeu) {
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
    int eau=0;
        for(int i = 0; i < jeu->nb_maisons; i++){
            eau+=jeu->maisons[i].eau;

        }
        jeu->eau= jeu->tot_eau - eau;

}

void calcul_elec(Jeu* jeu){
    int elec=0, electot=0;

        for (int i = 0; i < jeu->nb_maisons; i++) {
            elec += jeu->maisons[i].electricite;
        }
        electot = jeu->tot_electricite - elec;
        jeu->electricite = electot;
}

void compteur_population(Jeu* jeu){
    int pop=0;
    if(jeu->nb_maisons != 0){
        for(int i = 0; i < jeu->nb_maisons; i++){
            pop += jeu->maisons[i].habitants;
        }
    }jeu->population = pop;
}

void afficherCompteur(Jeu jeu) {
    printf("\n");
    printf("Electricite : %d/%d         ", jeu.electricite, jeu.tot_electricite);
    printf("Eau : %d/%d         ", jeu.eau, jeu.tot_eau);
    printf("Argent : %d         ", jeu.argent);
    printf("Population : %d\n", jeu.population);
    printf("\n");
}