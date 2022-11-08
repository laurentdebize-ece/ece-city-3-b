#include "initialisation_liberation.h"
#include <stdlib.h>

#define ARGENT_INITIAL 500000

Jeu initialisation_jeu(){
    Jeu jeu;
    jeu.argent = ARGENT_INITIAL;
    jeu.eau = 0;
    jeu.electricite = 0;
    jeu.population = 0;
    jeu.tot_eau = 0;
    jeu.tot_electricite = 0;
    jeu.nb_maisons = 0;
    jeu.nb_routes = 0;
    jeu.nb_centrales = 0;
    jeu.nb_chateau_eau = 0;
    jeu.map = initialisation_map();
    jeu.maisons = initialisation_maison();
    jeu.routes = initialisation_route();
    jeu.batiments = initialisation_batiment();

    return jeu;
}

void liberation_jeu(Jeu* jeu){
    liberation_map(&(jeu->map));
    jeu->map = NULL;
    liberation_maison(&(jeu->maisons));
    jeu->maisons = NULL;
    liberation_route(&(jeu->routes));
    jeu->routes = NULL;
    liberation_batiment(&(jeu->batiments));
    jeu->batiments = NULL;
}

Case** initialisation_map(){
    Case** map = malloc(sizeof(Case*)*TAILLE_MAP_X);
    for(int i = 0; i < TAILLE_MAP_X; i++){
        map[i] = malloc(sizeof(Case)*TAILLE_MAP_Y);
    }

    for(int i = 0; i < TAILLE_MAP_X; i++){
        for(int j = 0; j < TAILLE_MAP_Y; j++){
            map[i][j].occupe = false;
            map[i][j].symbole = SYMBOLE_VIDE;
        }
    }

    return map;
}

void liberation_map(Case*** map){
    for(int i = 0; i < TAILLE_MAP_X; i++){
        free((*map)[i]);
    }
    free(*map);
    *map = NULL;
}

Route* initialisation_route(){
    Route* routes = malloc(sizeof(Route)*NB_MAX_ROUTES);
    for(int i = 0; i < NB_MAX_ROUTES; i++){
        routes[i].pos_x = 0;
        routes[i].pos_y = 0;
        routes[i].adjacente_maison = NULL;
        routes[i].adjacente_route = NULL;
        routes[i].adjacente_batiment = NULL;
    }
    return routes;
}

void liberation_route(Route** route){
    free(*route);
    *route = NULL;
}

Batiment* initialisation_batiment(){
    Batiment* batiments = malloc(sizeof(Batiment)*NB_MAX_BATIMENTS);
    for(int i = 0; i < NB_MAX_BATIMENTS; i++){
        batiments[i].pos_x = 0;
        batiments[i].pos_y = 0;
        batiments[i].type_batiment = 0;
        batiments[i].capacite = 0;
        batiments[i].horizontal = false;
        batiments[i].routeAdjacente = NULL;
    }
    return batiments;
}

void liberation_batiment(Batiment** batiment){
    free(*batiment);
    *batiment = NULL;
}

Maison* initialisation_maison(){
    Maison* maisons = malloc(sizeof(Maison)*NB_MAX_MAISONS);
    for(int i = 0; i < NB_MAX_MAISONS; i++){
        maisons[i].pos_x = 0;
        maisons[i].pos_y = 0;
        maisons[i].niveau = 0;
        maisons[i].habitants = 0;
        maisons[i].eau = 0;
        maisons[i].electricite = 0;
        maisons[i].routeAdjacente = NULL;
    }
    return maisons;
}

void liberation_maison(Maison** maison){
    free(*maison);
    *maison = NULL;
}