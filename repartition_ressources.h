#ifndef ECE_CITY_3B_REPARTITION_RESSOURCES_H
#define ECE_CITY_3B_REPARTITION_RESSOURCES_H

#include "structure.h"

void repartition_ressources(Jeu* jeu);

void repartition_eau(Jeu* jeu);

void repartition_electricite(Jeu* jeu);
void composantes_connexes(Jeu* jeu, int* nb_composantes, Liste** composantes_maisons,Liste** composantes_centrales);
void dfs_recursif_recherche_cc(Jeu* jeu, Route *route,Liste ** composantes_maisons,Liste ** composantes_centrales);
Liste* tri_maisons(Jeu* jeu, Liste* maisons);

void repartition_habitants(Jeu* jeu);

#endif //ECE_CITY_3B_REPARTITION_RESSOURCES_H