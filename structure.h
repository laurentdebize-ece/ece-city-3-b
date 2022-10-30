#ifndef ECE_CITY_3B_STRUCTURE_H
#define ECE_CITY_3B_STRUCTURE_H

#include "liste.h"
#include <stdbool.h>

#define TYPE_ROUTE 0
#define TYPE_MAISON 1
#define TYPE_BATIMENT 2
#define TYPE_CENTRALE 3
#define TYPE_CHATEAU_EAU 4

#define PRIX_ROUTE 10
#define PRIX_CENTRALE 100000
#define PRIX_CHATEAU_EAU 100000
#define PRIX_MAISON 1000

#define TAILLE_MAISON 3
#define TAILLE_GRANDE_BATIMENT 6
#define TAILLE_PETITE_BATIMENT 4

#define CAPACITE_BATIMENTS 5000

// case de la map
typedef struct Case{
    bool occupe;
    char symbole;
    int pos_x;
    int pos_y;
}Case;

typedef struct Route{
    char symbole;
    int pos_x;
    int pos_y;
    struct Liste* adjacente_maison;
    struct Liste* adjacente_route;
    struct Liste* adjacente_batiment;
}Route;
// contient les centrales et les chateaux d'eau
typedef struct Batiment{
    char symbole;
    int type_batiment;
    int capacite;
    int pos_x;
    int pos_y;
    bool horizontal;
    struct Liste* routeAdjacente;
}Batiment;

typedef struct Maison{
    char symbole;
    int niveau;
    int habitants;
    int eau;
    int electricite;
    struct Liste* routeAdjacente;
    int pos_x;
    int pos_y;
}Maison;

typedef struct Jeu{
    int argent;
    Case** map;
    Route* routes;
    int nb_routes;
    Batiment* batiments;
    int nb_centrales;
    int nb_chateau_eau;
    Maison* maisons;
    int nb_maisons;
}Jeu;



#endif //ECE_CITY_3B_STRUCTURE_H
