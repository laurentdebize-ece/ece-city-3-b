//
// Created by Mona Lias on 11/15/22.
//

#include "eau.h"
#include <stdlib.h>

void initialisationFiles_chateaux(Jeu *jeu, int *tab_indice_chateau, File **tab_file) {
    int nbChateau = 0;
    tab_indice_chateau = malloc(sizeof(int) * jeu->nb_chateau_eau);
    tab_file = malloc(sizeof(File *) * jeu->nb_chateau_eau);
    for (int i=0; i<jeu->nb_chateau_eau; i++){
        tab_file[i] = NULL;
    }
    for (int i = 0; i < jeu->nb_chateau_eau; i++) {
        // on parcours tous les batiments du jeu jusqu'a trouver un chateau
        if (jeu->batiments[i].type_batiment == TYPE_CHATEAU_EAU) {
            // on remplit le tableau avec l'indice du chateau
            tab_indice_chateau[nbChateau] = i;
            // tant qu'il existe des routes adjacentes au chateau
            Liste * tmp = jeu->batiments[i].routeAdjacente; // VERIFIEZ QUE DANS LE BFS CA NE MODIFIE PAS TOUTE L'ADJACENCE
            while (tmp != NULL) {
                // enfiler chaque routes adjacentes au chateau dans la file qui lui correspond
                enfiler(&tab_file[nbChateau], jeu->batiments[i].routeAdjacente->numero);
                tmp = tmp->suivant;
            }
            nbChateau++;
        }
    }
}

bool fonctionTest(Jeu *jeu, File *file, int *tab_indice_chateau) {
    int indice;
    bool ok=false;
    Batiment chateau;
    for (int i = 0; i < jeu->nb_chateau_eau; i++) {
        indice = tab_indice_chateau[i];
        chateau = jeu->batiments[indice];
        if (chateau.capacite == 0 || file[i].suivant == NULL) {
            ok = true;
            i = jeu->nb_chateau_eau;
        } else {
            ok = false;
        }
    }
    return ok;
}

char** init_marquage(Jeu *jeu) {
    char** marquage = malloc (jeu->nb_routes*(sizeof (Route)));
    for (int i = 0; i< jeu->nb_chateau_eau ; i++){
        marquage [i] = malloc (sizeof (Batiment));
    }
    for (int i = 0; i<jeu->nb_chateau_eau; i++){
        for (int j=0; j<jeu->nb_routes; j++){
            marquage[i][j]=NON_MARQUE;
        }
    }
    return marquage;
}

void liberer_tab_marquage( Jeu * jeu,  char ** marquage){
    for (int i = 0; i<jeu->nb_chateau_eau; i++){
        for (int j=0; i<jeu->nb_routes; j++) {
            free(&marquage[i][j]);
        }
    }
}

// fonction pour determiner la capacite_max de la maison en fonction de son niveau d'evolution = nb d'habitants
int capacite_totale_maison(Jeu* jeu, int numero){
    Maison maison = jeu->maisons[numero];
    int capacite_max, capacite_act;
    capacite_act = maison.eau;
    if (maison.habitants == 0 && maison.habitants <= 10){
        capacite_max = 10 - capacite_act ;
    }
    else if (maison.habitants > 10 && maison.habitants <= 50){
        capacite_max = 50 - capacite_act;
    } else if (maison.habitants > 50 && maison.habitants <= 100){
        capacite_max = 100 - capacite_act;
    } else if (maison.habitants > 100 && maison.habitants <= 1000){
        capacite_max = 1000 - capacite_act;
    } else {
        capacite_max = 0 - capacite_act;
    }
    return capacite_max;
}

void remplir_maison(int* num_maison, int num_route, Jeu* jeu, Batiment * chateau, int capacite_maison){
    // on recupere la maison a l'aide de son num dans le jeu
    *num_maison =jeu->routes[num_route].adjacente_maison->numero;
    // on definit sa capacite maximale en eau
    capacite_maison = capacite_totale_maison(jeu, *num_maison);
    // si la maison n'est pas pleine
    if (jeu->maisons[*num_maison].eau < capacite_maison) {
        // si la capacite du chateau peut remplir la maison
        if (chateau->capacite >= capacite_maison) {
            // on remplit la maison en entier
            chateau->capacite = chateau->capacite - capacite_maison;
            jeu->maisons[*num_maison].eau = jeu->maisons[*num_maison].eau + capacite_maison;
        }
        else {
            jeu->maisons[*num_maison].eau = jeu->maisons[*num_maison].eau + chateau->capacite;
            chateau->capacite = 0;
        }
    }
}


void BFS_eau(Jeu *jeu, File *file, int indice_chateau, Batiment * chateau, char** marquage) {
    file = chateau->routeAdjacente;
    int num_maison, capacite_maison;
    // on recupere la premiere route de la file = premiere route adjacente au chateau
    while (chateau->capacite != 0 || file != NULL){
    int num_route = defiler(&file);
    // si la route n'est pas deja marquée par le chateau
    if (marquage [num_route][indice_chateau] != NON_MARQUE){
        Liste * tmp = jeu->routes[num_route].adjacente_maison;
        // tant que la route possede une maison adjacente
        while (tmp != NULL ){
            // on recuperere la maison dans le jeu à l'aide de son num
            num_maison = tmp->numero ;
            capacite_maison = jeu->maisons[num_maison].eau;
            remplir_maison(&num_maison, num_route, jeu, chateau, capacite_maison);
            tmp = tmp->suivant;
        }
        // si la route possede une route adjacente
        tmp = jeu->routes[num_route].adjacente_route;
        while (tmp!=NULL){
            int newRoute = jeu->routes[num_route].adjacente_route->numero;
            enfiler(&file, newRoute);
            tmp= tmp->suivant;
        }
    }
    // on marque la route
    marquage[num_route][indice_chateau] = (char)indice_chateau;
    }
}


void repartitionEau(Jeu *jeu) {
    File *tabFiles;
    int *tab_indice_chateau;
    int indice;
    Batiment chateau;
    char** marquage;
    initialisationFiles_chateaux(jeu, &tab_indice_chateau, &tabFiles);
    marquage= init_marquage(jeu);
    bool continuer = 1;
    // on creer une boucle pour pouvoir tester si chateau non vide & si file non vide a la fin de chaque cycle de BFS
    while (continuer == true) {
        for (int i = 0; i < jeu->nb_chateau_eau; i++) {
            // on recupere l'indice dans le tab pour pouvoir le relier à un chateau d'eau de type Batiment
            indice = tab_indice_chateau[i];
            chateau = jeu->batiments[indice];
            // on teste si le chateau non vide et si sa file non vide
            if (fonctionTest(jeu, &tabFiles[indice], &tab_indice_chateau[indice]) == false) {
                // si ça n'est pas le cas on lance un BFS sur le chateau en passant en parametre sa liste de routes adjacentes
                BFS_eau(jeu, &tabFiles[indice], indice, &chateau, marquage);
                liberer_tab_marquage(jeu, marquage);
            }
        }
        continuer = 0;
        // apres avoir effectuer tous les BFS on verifie une seconde fois que tous les chateaux ne soient pas vides et que toutes les files non plus
        for (int i = 0; i < jeu->nb_chateau_eau; i++) {
            if (fonctionTest(jeu, tabFiles, &tab_indice_chateau[i]) == true) {
                continuer = false;
            } else {
                continuer = true;
            }
            // si ça n'est pas le cas on relance à nouveau des BFS
            // si tout est vide alors il n'y a plus d'eau a distribuer et on arrete la distribution tant qu'un nouveau chateau n'est pas construit
        }
    }

}