//
// Created by Mona Lias on 11/15/22.
//

#include "eau.h"
#include <stdlib.h>
#include "debug.h"

void initialisationFiles_chateaux(Jeu *jeu, int *tab_indice_chateau, File **tab_file, char **marquage) {
    int nbChateau = 0;
    for (int i = 0; i < jeu->nb_chateau_eau + jeu->nb_centrales; i++) {
        // on parcours tous les batiments du jeu jusqu'a trouver un chateau
        if (jeu->batiments[i].type_batiment == TYPE_CHATEAU_EAU) {
            // on remplit le tableau avec l'indice du chateau
            tab_indice_chateau[nbChateau] = i;
            // tant qu'il existe des routes adjacentes au chateau
            Liste *tmp = jeu->batiments[i].routeAdjacente; // VERIFIEZ QUE DANS LE BFS CA NE MODIFIE PAS TOUTE L'ADJACENCE
            while (tmp != NULL) {
                // enfiler chaque routes adjacentes au chateau dans la file qui lui correspond
                enfiler(&(tab_file[nbChateau]), tmp->numero);
                marquage[tmp->numero][nbChateau] = (char) nbChateau;
                tmp = tmp->suivant;
            }
            nbChateau++;
        }
    }
}

bool fonctionTest(Jeu *jeu, File *file, int *tab_indice_chateau) {
    int indice;
    Batiment chateau;
    indice = *tab_indice_chateau;
    chateau = jeu->batiments[indice];
    if (chateau.capacite == 0 || file == NULL) {
        return true;
    } else {
        return false;
    }
}

char **init_marquage(Jeu *jeu) {
    char **marquage = malloc(jeu->nb_routes * (sizeof(char *)));
    for (int i = 0; i < jeu->nb_routes; i++) {
        marquage[i] = malloc(sizeof(char) * jeu->nb_chateau_eau);
    }
    for (int i = 0; i < jeu->nb_routes; i++) {
        for (int j = 0; j < jeu->nb_chateau_eau; j++) {
            marquage[i][j] = NON_MARQUE;
        }
    }
    return marquage;
}

void liberer_tab_marquage(Jeu *jeu, char **marquage) {
    for (int i = 0; i < jeu->nb_routes; i++) {
        free(marquage[i]);
    }
    free(marquage);
    marquage = NULL;
}

// fonction pour determiner la capacite_max de la maison en fonction de son niveau d'evolution = nb d'habitants
int capacite_totale_maison(Jeu *jeu, int numero) {
    Maison maison = jeu->maisons[numero];
    int capacite_max, capacite_act;
    capacite_act = maison.eau;
    if (maison.niveau == NIVEAU_CABANE) {
        capacite_max = HAB_MAX_CABANE - capacite_act;
    } else if (maison.niveau == NIVEAU_MAISON) {
        capacite_max = HAB_MAX_MAISON - capacite_act;
    } else if (maison.niveau == NIVEAU_IMMEUBLE) {
        capacite_max = HAB_MAX_IMMEUBLE - capacite_act;
    } else if (maison.niveau == NIVEAU_GRATTE_CIEL) {
        capacite_max = HAB_MAX_GRATTE_CIEL - capacite_act;
    } else if (maison.niveau == NIVEAU_RUINE) {
        capacite_max = 0;
    } else {
        capacite_max = 0;
    }
    return capacite_max;
}

void remplir_maison(int num_maison,Jeu *jeu, int indice_chateau) {
    // on definit sa capacite maximale en eau
    int capacite_maison = capacite_totale_maison(jeu, num_maison);
    // si la maison n'est pas pleine
    if (capacite_maison > 0) {
        // si la capacite du chateau peut remplir la maison
        if (jeu->batiments[indice_chateau].capacite >= capacite_maison) {
            // on remplit la maison en entier
            jeu->batiments[indice_chateau].capacite -= capacite_maison;
            jeu->maisons[num_maison].eau += capacite_maison;
        } else {
            jeu->maisons[num_maison].eau += jeu->batiments[indice_chateau].capacite;
            jeu->batiments[indice_chateau].capacite = 0;
        }
    }
}


void BFS_eau(Jeu *jeu, File **file, Batiment *chateau, char **marquage,int indice,int* indices_chateaux) {
    int num_maison;
    // on recupere la premiere route de la file = premiere route adjacente au chateau
    if (chateau->capacite != 0 && *file != NULL) {
        int num_route = defiler(file);
        // si la route n'est pas deja marqu??e par le chateau
        if (num_route != -1) {
            Liste *tmp = jeu->routes[num_route].adjacente_maison;
            // tant que la route possede une maison adjacente
            while (tmp != NULL) {
                // on recuperere la maison dans le jeu ?? l'aide de son num
                num_maison = tmp->numero;
                remplir_maison(num_maison, jeu, indices_chateaux[indice]);
                tmp = tmp->suivant;
            }
            // si la route possede une route adjacente
            tmp = jeu->routes[num_route].adjacente_route;
            while (tmp != NULL) {
                int newRoute = tmp->numero;
                if (marquage[newRoute][indice] == NON_MARQUE) {
                    enfiler(file, newRoute);
                    // on marque la route apres l'avoir enfile
                    marquage[newRoute][indice] = (char) indice;
                }
                tmp = tmp->suivant;
            }
        }
    }
}


void repartitionEau(Jeu *jeu) {
    // on reset toutes les capacit??s des chateaux et l'eau des maisons avant de commencer
    for (int i = 0; i < jeu->nb_chateau_eau+jeu->nb_centrales; i++) {
        jeu->batiments[i].capacite = CAPACITE_BATIMENTS;
    }
    for (int i = 0; i < jeu->nb_maisons; i++) {
        jeu->maisons[i].eau = 0;
    }

    // on initialise les variables n??cessaires pour le BFS et etc.
    File **tab_file;
    int *tab_indice_chateau;
    int indice;
    char **marquage = init_marquage(jeu);
    tab_indice_chateau = malloc(sizeof(int) * jeu->nb_chateau_eau);
    tab_file = malloc(sizeof(File *) * jeu->nb_chateau_eau);
    for (int i = 0; i < jeu->nb_chateau_eau; i++) {
        tab_file[i] = NULL;
    }
    initialisationFiles_chateaux(jeu, tab_indice_chateau, tab_file, marquage);
    bool continuer = 1;
    // on creer une boucle pour pouvoir tester si chateau non vide & si file non vide a la fin de chaque cycle de BFS
    while (continuer == true) {
        for (int i = 0; i < jeu->nb_chateau_eau; i++) {
            // on recupere l'indice dans le tab pour pouvoir le relier ?? un chateau d'eau de type Batiment
            BFS_eau(jeu, &(tab_file[i]), &jeu->batiments[tab_indice_chateau[i]], marquage, i, tab_indice_chateau);
        }
        continuer = 0;
        // apres avoir effectuer tous les BFS on verifie une seconde fois que tous les chateaux ne soient pas vides et que toutes les files non plus
        for (int i = 0; i < jeu->nb_chateau_eau; i++) {
            if ((fonctionTest(jeu, tab_file[i], &tab_indice_chateau[i]) == false)) {
                continuer = true;
            }
            // si ??a n'est pas le cas on relance ?? nouveau des BFS
            // si tout est vide alors il n'y a plus d'eau a distribuer et on arrete la distribution tant qu'un nouveau chateau n'est pas construit
        }
    }
    liberer_tab_marquage(jeu, marquage);
    free(tab_indice_chateau);
    for (int i = 0; i < jeu->nb_chateau_eau; i++) {
        free_file(&(tab_file[i]));
    }
    free(tab_file);
    tab_file = NULL;
    tab_indice_chateau = NULL;


}