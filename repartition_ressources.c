#include "repartition_ressources.h"
#include <stdlib.h>

void repartition_ressources(Jeu* jeu);

void repartition_eau(Jeu* jeu);

void repartition_electricite(Jeu* jeu){
    Liste** composantes_maisons,composantes_centrales;
    int nb_composantes;
    composantes_connexes(jeu,&nb_composantes,&composantes_maisons,&composantes_centrales);

    for (int i = 0;i < nb_composantes;i++){
        composantes_maisons[i] = tri_maisons(jeu,composantes_maisons[i]);
    }

    int* capacites_centrales = malloc(sizeof(int)*(jeu->nb_centrales+jeu->nb_chateau_eau));
    for (int i = 0;i < jeu->nb_centrales+jeu->nb_chateau_eau;i++){
        capacites_centrales[i] = CAPACITE_BATIMENTS;
    }

    for (int i = 0;i < nb_composantes;i++){
        Liste* tmp = composantes_centrales[i];
        int capacite_totale = 0;
        while(tmp != NULL){}
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

void repartition_habitants(Jeu* jeu);