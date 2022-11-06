#include "initialisation.h"


void init(int* argent, int* eau, int* electricite, int* nb_habitant ){
    *argent = 500000;
    *eau = 0;
    *electricite = 0;
    *nb_habitant = 0;
}

void impot(int* argent, int* nb_habitant){
    *argent = *argent + *nb_habitant*10;
}
