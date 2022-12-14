#ifndef ECE_CITY_3B_STRUCTURE_H
#define ECE_CITY_3B_STRUCTURE_H

#include "liste.h"
#include <stdbool.h>
#include "time.h"


#define MODE_CAPITALISTE 1
#define MODE_COMMUNISTE 2

#define NIVEAU_TERRAIN_VAGUE 0
#define NIVEAU_RUINE -1
#define NIVEAU_CABANE 1
#define NIVEAU_MAISON 2
#define NIVEAU_IMMEUBLE 3
#define NIVEAU_GRATTE_CIEL 4
#define HAB_MAX_CABANE 10
#define HAB_MAX_MAISON 50
#define HAB_MAX_IMMEUBLE 100
#define HAB_MAX_GRATTE_CIEL 1000

#define TAILLE_MAP_X 45
#define TAILLE_MAP_Y 35

#define NB_MAX_ROUTES TAILLE_MAP_X*TAILLE_MAP_Y
#define NB_MAX_BATIMENTS TAILLE_MAP_X*TAILLE_MAP_Y/(TAILLE_GRANDE_BATIMENT*TAILLE_PETITE_BATIMENT)
#define NB_MAX_MAISONS TAILLE_MAP_X*TAILLE_MAP_Y/(TAILLE_MAISON*TAILLE_MAISON)

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

#define SYMBOLE_ROUTE 'R'
#define SYMBOLE_MAISON 'M'
#define SYMBOLE_CENTRALE 'C'
#define SYMBOLE_CHATEAU_EAU 'E'
#define SYMBOLE_VIDE '*'

#define NON_MARQUE -1
// affichage en travaux

#define LARGEUR_ECRAN 1280
#define HAUTEUR_ECRAN 720
#define TAILLE_PLATEAU 50
#define LARGEUR_PLATEAU 35
#define LONGUEUR_PLATEAU 45

#define VERT_HERBE CLITERAL(Color){ 124, 252, 0, 255 }
#define VERT_SOL CLITERAL(Color){ 20,212,0,255}

#define FLT_MAX     340282346638528859811704183484516925440.0f

typedef struct{
    float pos_x;
    float pos_y;
    float pos_z;
}Position;




// affichage en travaux

// case de la map
typedef struct Case{
    bool occupe;
    char symbole;
    float x, z, largeur, hauteur;

}Case;

typedef struct Route{
    int pos_x;
    int pos_y;
    Position position;
    struct Liste* adjacente_maison;
    struct Liste* adjacente_route;
    struct Liste* adjacente_batiment;
}Route;
// contient les centrales et les chateaux d'eau
typedef struct Batiment{
    int type_batiment;
    int capacite;
    int pos_x;
    int pos_y;
    Position position;
    bool horizontal;
    struct Liste* routeAdjacente;
}Batiment;

typedef struct Maison{
    int niveau;
    int habitants;
    int eau;
    int electricite;
    struct Liste* routeAdjacente;
    int pos_x;
    int pos_y;
    int timer;
    Position position;
    int compteur_evolution;
}Maison;

typedef struct Jeu{
    int mode_jeu;
    int argent;
    int eau;
    int electricite;
    int population;
    int tot_eau;
    int tot_electricite;
    Case** map;
    Route* routes;
    int nb_routes;
    Batiment* batiments;
    int nb_centrales;
    int nb_chateau_eau;
    Maison* maisons;
    int nb_maisons;
    time_t temps;
    int compteur_impot;
}Jeu;



#endif //ECE_CITY_3B_STRUCTURE_H
