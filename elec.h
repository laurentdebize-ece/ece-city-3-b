#ifndef ECE_CITY_3B_ELEC_H
#define ECE_CITY_3B_ELEC_H

#include "structure.h"

void repartition_electricite(Jeu* jeu);
void composantes_connexes(Jeu* jeu, int* nb_composantes, Liste*** composantes_maisons,Liste*** composantes_centrales);
void dfs_recursif_recherche_cc(Jeu* jeu, int route,Liste** composantes_maisons,Liste** composantes_centrales,int** marquage);
Liste* tri_maisons(Jeu* jeu, Liste* maisons);
Liste** tri_centrales(Jeu* jeu,Liste** composantes_centrales, int nb_composantes);

void repartition_habitants(Jeu* jeu);
int nb_habitants_max(int niveau);

#endif //ECE_CITY_3B_ELEC_H