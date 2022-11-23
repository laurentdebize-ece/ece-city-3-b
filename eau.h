//
// Created by Mona Lias on 11/15/22.
//

#ifndef FICHIER_H_EAU_H
#define FICHIER_H_EAU_H
#include "structure.h"
#include "liste.h"
#include <stdio.h>


// fonction test avant BFS
void initialisationFiles_chateaux(Jeu *jeu, int *tab_indice_chateau, File **tab_file, char** marquage);
bool fonctionTest(Jeu *jeu, File *file, int *tab_indice_chateau);

// fonctions pour marquer les routes lorsqu'elles ont ete decouvertes par un chateau
char** init_marquage(Jeu *jeu);
void liberer_tab_marquage( Jeu * jeu,  char ** marquage);

// fonction pour gerer le remplissage des maison en fonction de sa capacite et de son evolution
int capacite_totale_maison(Jeu* jeu, int numero);
void remplir_maison(int* num_maison, int num_route, Jeu* jeu, int indice_chateau, int capacite_maison);

// fonction BFS pour parcourir toutes les routes et tous les chateau en meme temps
void BFS_eau(Jeu *jeu, File **file, int indice_chateau, Batiment * chateau, char** marquage);

// fonction qui met toutes les fonctions precedentes en commun pour pouvoir effectuer la repartition de l'eau
void repartitionEau(Jeu *jeu);


#endif //FICHIER_H_EAU_H
