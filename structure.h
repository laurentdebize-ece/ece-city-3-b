#ifndef ECE_CITY_3B_STRUCTURE_H
#define ECE_CITY_3B_STRUCTURE_H


typedef struct Liste {
    struct Liste* suivant;
    int numero;
};

typedef struct Route{
    char symbole;
    int pos_x;
    int pos_y;
    struct Liste* adjacente_maison;
    struct Liste* adjacente_route;
    struct Liste* adjacente_batiment;
};

typedef struct Case{
    int occupe;
    char symbole;
    int pos_x;
    int pos_y;
};

typedef struct Batiment{
    char symbole;
    int capacite;
    int pos_x;
    int pos_y;
    struct Liste* routeAdjacente;
};

typedef struct Maison{
    char symbole;
    int niveau;
    int eau;
    int electricite;
    struct Liste* routeAdjacente;
    int pos_x;
    int pos_y;
};


#endif //ECE_CITY_3B_STRUCTURE_H
