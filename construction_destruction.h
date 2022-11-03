#ifndef ECE_CITY_3B_CONSTRUCTION_DESTRUCTION_H
#define ECE_CITY_3B_CONSTRUCTION_DESTRUCTION_H

#include "structure.h"

/**************************************Construire***********************************************/

bool batiment_sur_map(int pos_x, int pos_y, int taille_x, int taille_y);
bool check_argent(int argent_joueur, int argent_demande);

int** detecter_cases_interieur(Jeu* jeu,int pos_x,int pos_y,int taille_x,int taille_y);
int** detecter_cases_adjacentes(Jeu* jeu,int pos_x,int pos_y,int taille_x,int taille_y,int* taille_tab);

bool pas_de_batiment_sur_position(Jeu* jeu,int** tableau_cases_interieurs,int taille_tab);
void mettre_cases_occupees(Jeu* jeu,int pos_x,int pos_y,int taille_x,int taille_y,char symbole,int numero);

Liste* detecter_routes_adjacentes(Route* routes,int nb_routes,int** tableau_cases_adjacentes,int taille_tab);
Liste* detecter_maisons_adjacentes(Maison* maisons,int nb_maisons,int** tableau_cases_adjacentes,int taille_tab);
Liste* detecter_batiements_adjacents(Batiment* batiments,int nb_batiments,int** tableau_cases_adjacentes,int taille_tab);
Liste** detecter_elements_adjacents(Jeu* jeu,int type,int pos_x,int pos_y,int taille_x,int taille_y);

void construire_maison(Jeu* jeu,int pos_x,int pos_y,Liste** elements_adjacents);
void construire_batiment(Jeu* jeu,int pos_x,int pos_y,int type_batiment,bool horizontal,Liste** elements_adjacents);
void construire_route(Jeu* jeu,int pos_x,int pos_y,Liste** elements_adjacents);

bool construire(Jeu* jeu,int type_batiment,int pos_x,int pos_y,bool horizontal);

/************************************Fin Construire*********************************************/

/***************************************Détruire***********************************************/

void faire_moins_un_si_sup_num(Liste** liste,int numero);
void mettre_cases_inoccupees(Jeu* jeu,int** tableau_cases_interieurs,int taille_tab);

bool detruire_maison(Jeu* jeu, int numero);
bool detruire_batiment(Jeu* jeu, int numero,int type_batiment);
bool detruire_route(Jeu* jeu, int pos_x,int pos_y);

bool detruire(Jeu* jeu, int type_batiment, int numero,int pos_x,int pos_y);

/*************************************Fin Détruire*********************************************/


#endif