#ifndef ECE_CITY_3B_STRUCTURE_H
#define ECE_CITY_3B_STRUCTURE_H

//creation d'une liste pour pouvoir determiner les routes adjacentes a chaque batiment et les batiments adjacents aux autres
typedef struct Liste {
    struct Liste* suivant;
    int numero;
};

// case de la map
typedef struct Case{
    int occupe;
    char symbole;
    int pos_x;
    int pos_y;
};

typedef struct Route{
    char symbole;
    int pos_x;
    int pos_y;
    struct Liste adjacente_maison;
    struct Liste adjacente_route;
    struct Liste adjacente_batiment;
};
// contient les centrales et les chateaux d'eau
typedef struct Batiment{
    char symbole;
    int capacite;
    int pos_x;
    int pos_y;
    struct Liste routeAdjacente;
};

typedef struct Maison{
    char symbole;
    int niveau;
    int eau;
    int electricite;
    struct Liste routeAdjacente;
    int pos_x;
    int pos_y;
};


#endif //ECE_CITY_3B_STRUCTURE_H
