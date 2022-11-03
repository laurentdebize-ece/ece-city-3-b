#include "debug.h"

void afficher_matrice_int(int** matrice, int taille_x, int taille_y){
    for(int i=0; i<taille_x; i++){
        printf("\t%d",i);
    }
    for(int i = 0; i < taille_y; i++){
        printf("\n%d",i);
        for(int j = 0; j < taille_x; j++){
            printf("\t%d", matrice[j][i]);
        }
    }
    printf("\n");
}