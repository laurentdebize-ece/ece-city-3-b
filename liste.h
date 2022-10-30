#ifndef ECE_CITY_3B_LISTE_H
#define ECE_CITY_3B_LISTE_H

//creation d'une liste pour pouvoir determiner les routes adjacentes a chaque batiment et les batiments adjacents aux autres
typedef struct Liste {
    struct Liste* suivant;
    int numero;
}Liste;

void ajouter_liste (struct Liste** liste, int numero);
void retirer_liste (struct Liste** liste, int numero);
void free_liste (struct Liste** liste);

#endif