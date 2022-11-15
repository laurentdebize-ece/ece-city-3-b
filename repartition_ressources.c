#include "repartition_ressources.h"
#include "liste.h"
#include <stdlib.h>

void repartition_ressources(Jeu* jeu);

void repartition_eau(Jeu* jeu);

void repartition_electricite(Jeu* jeu){
    Liste** composantes_maisons;
    Liste** composantes_centrales;
    int nb_composantes;
    composantes_connexes(jeu,&nb_composantes,&composantes_maisons,&composantes_centrales);

    for (int i = 0;i < nb_composantes;i++){
        composantes_maisons[i] = tri_maisons(jeu,composantes_maisons[i]);
    }
    composantes_centrales = tri_centrales(jeu,composantes_centrales,nb_composantes);

    int* capacites_centrales = malloc(sizeof(int)*(jeu->nb_centrales+jeu->nb_chateau_eau));
    for (int i = 0;i < jeu->nb_centrales+jeu->nb_chateau_eau;i++){
        capacites_centrales[i] = CAPACITE_BATIMENTS;
    }

    for (int i = 0;i < nb_composantes;i++){
        Liste* tmp = composantes_centrales[i];
        int capacite_totale = 0;
        while(tmp != NULL){
            capacite_totale += capacites_centrales[tmp->numero];
            tmp = tmp->suivant;
        }
        // répartir l'électricité totale dans les maisons
        tmp = composantes_maisons[i];
        while(tmp != NULL){
            int habitants_max = nb_habitants_max(jeu->maisons[tmp->numero].niveau);
            if (capacite_totale >= habitants_max){
                jeu->maisons[tmp->numero].electricite = habitants_max;
                capacite_totale -= habitants_max;
            }
            tmp = tmp->suivant;
        }
        // rerépartir l'electricité restante dans capacites_centrales
        tmp = composantes_centrales[i];
        while(tmp != NULL){
            if (capacites_centrales > CAPACITE_BATIMENTS){
                capacites_centrales[tmp->numero] = CAPACITE_BATIMENTS;
                capacite_totale -= CAPACITE_BATIMENTS;
            }
            else{
                capacites_centrales[tmp->numero] = capacite_totale;
                capacite_totale = 0;
            }

            tmp = tmp->suivant;
        }
    }
}

void composantes_connexes(Jeu* jeu, int* nb_composantes, Liste*** composantes_maisons,Liste*** composantes_centrales){
    // allocations des listes
    *composantes_maisons = malloc(sizeof(Liste*)*jeu->nb_maisons);
    for (int i = 0; i < jeu->nb_maisons; i++){
        composantes_maisons[i] = NULL;
    }
    *composantes_centrales = malloc(sizeof(Liste*)*jeu->nb_centrales);
    for (int i = 0; i < jeu->nb_centrales; i++){
        composantes_centrales[i] = NULL;
    }

    // allocations des marquages
    int **marquage = malloc(sizeof(int*)*3);
    marquage[TYPE_ROUTE] = malloc(sizeof(int)*jeu->nb_routes);
    for(int i = 0; i < jeu->nb_routes; i++){
        marquage[TYPE_ROUTE][i] = 0;
    }
    marquage[TYPE_MAISON] = malloc(sizeof(int)*jeu->nb_maisons);
    for(int i = 0; i < jeu->nb_maisons; i++){
        marquage[TYPE_MAISON][i] = 0;
    }
    marquage[TYPE_CENTRALE] = malloc(sizeof(int)*(jeu->nb_centrales*jeu->nb_chateau_eau));
    for(int i = 0; i < jeu->nb_centrales*jeu->nb_chateau_eau; i++){
        marquage[TYPE_CENTRALE][i] = 0;
    }

    // recherches des composantes connexes
    *nb_composantes = 0;
    for(int i = 0; i < jeu->nb_routes; i++){
        if(marquage[TYPE_ROUTE][i] == 0){
            dfs_recursif_recherche_cc(jeu, i, (*composantes_maisons)[*nb_composantes], (*composantes_centrales)[*nb_composantes], marquage);
            (*nb_composantes)++;
        }
    }
}

void dfs_recursif_recherche_cc(Jeu* jeu, int route,Liste* composantes_maisons,Liste* composantes_centrales,int** marquage){
    marquage[TYPE_ROUTE][route] = 2;
    Liste* tmp = jeu->routes[route].adjacente_maison;
    while(tmp != NULL){
        if(marquage[TYPE_MAISON][tmp->numero] == 0){
            marquage[TYPE_MAISON][tmp->numero] = 1;
            ajouter_liste(&composantes_maisons,tmp->numero);
        }
    }
    tmp = jeu->routes[route].adjacente_batiment;
    while(tmp != NULL){
        if(jeu->batiments[tmp->numero].type_batiment == TYPE_CENTRALE && marquage[TYPE_BATIMENT][tmp->numero] == 0){
            marquage[TYPE_BATIMENT][tmp->numero] = 1;
            ajouter_liste(&composantes_centrales,tmp->numero);
        }
        tmp = tmp->suivant;
    }
    tmp = jeu->routes[route].adjacente_route;
    while(tmp != NULL){
        if(marquage[TYPE_ROUTE][tmp->numero] == 0){
            marquage[TYPE_ROUTE][tmp->numero] = 1;
            dfs_recursif_recherche_cc(jeu,tmp->numero,composantes_maisons,composantes_centrales,marquage);
        }
        tmp = tmp->suivant;
    }
}

Liste* tri_maisons(Jeu* jeu, Liste* maisons){
    Liste* triees = NULL;
    Liste* tmp = maisons;
    while(tmp != NULL){
        Liste* tmp2 = tmp;
        int moins_eau = tmp->numero; // moins eau pour que la liste soit triée par ordre croissant
        while(tmp2 != NULL){
            if(jeu->maisons[tmp2->numero].eau < jeu->maisons[moins_eau].eau){
                moins_eau = tmp2->numero;
            }
        }
        ajouter_liste(&triees,moins_eau);
        retirer_liste(&tmp,moins_eau);
    }
    return triees;
}

Liste** tri_centrales(Jeu* jeu,Liste** composantes_centrales, int nb_composantes){
    Liste** triees = malloc(sizeof(Liste*)*nb_composantes);
    for (int i = 0;i<nb_composantes;i++){
        triees[i] = NULL;   
    }

    int* dans_cb_cc = malloc(sizeof(int)*(jeu->nb_centrales+jeu->nb_chateau_eau));
    for (int i = 0;i<jeu->nb_centrales+jeu->nb_chateau_eau;i++){
        dans_cb_cc[i] = 0;
    }

    for(int i = 0; i < nb_composantes; i++){
        Liste* tmp = composantes_centrales[i];
        while(tmp != NULL){
            (dans_cb_cc[tmp->numero])++;
        }
    }

    for(int i = 0; i < nb_composantes; i++){
        while(composantes_centrales[i] != NULL){
            Liste* tmp = composantes_centrales[i];
            int min_dans_cb_cc = tmp->numero;
            while(tmp != NULL){
                if(dans_cb_cc[tmp->numero] < dans_cb_cc[min_dans_cb_cc]){
                    min_dans_cb_cc = tmp->numero;
                }
                tmp = tmp->suivant;
            }
            ajouter_liste(&triees[i],min_dans_cb_cc);
            retirer_liste(&composantes_centrales[i],min_dans_cb_cc);
        }
    }

    free(dans_cb_cc);
    free(composantes_centrales);

    return triees;
}

void repartition_habitants(Jeu* jeu){
    for(int i = 0; i < jeu->nb_maisons; i++){
        jeu->maisons[i].habitants = (jeu->maisons[i].eau<jeu->maisons[i].electricite)?jeu->maisons[i].eau:jeu->maisons[i].electricite;
    }
}

int nb_habitants_max(int niveau){
    switch(niveau){
        case NIVEAU_RUINE:
            return 0;
        case NIVEAU_TERRAIN_VAGUE:
            return 0;
        case NIVEAU_CABANE:
            return HAB_MAX_CABANE;
        case NIVEAU_MAISON:
            return HAB_MAX_MAISON;
        case NIVEAU_IMMEUBLE:
            return HAB_MAX_IMMEUBLE;
        case NIVEAU_GRATTE_CIEL:
            return HAB_MAX_GRATTE_CIEL;
        default:
            return 0;
    }
}