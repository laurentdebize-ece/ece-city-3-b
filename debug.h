#include<stdio.h>
#include "liste.h"

#define DEBUG 1
#define DEBUG_PRINT(x) if (DEBUG) { printf(x); fflush(stdout);}
#define DEBUG_PRINT_INT(x) if (DEBUG) { printf("%d ",x); fflush(stdout);}
#define DEBUG_PRINT_MATRICE(matrice,taille_x,taille_y) if (DEBUG) { afficher_matrice_int(matrice,taille_x,taille_y); fflush(stdout);}
#define DEBUG_PRINT_LISTE(liste) if (DEBUG) { afficher_liste(liste); fflush(stdout);}

void afficher_matrice_int(int** matrice, int taille_x, int taille_y);