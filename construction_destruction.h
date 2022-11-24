#ifndef ECE_CITY_3B_CONSTRUCTION_DESTRUCTION_H
#define ECE_CITY_3B_CONSTRUCTION_DESTRUCTION_H

#include "structure.h"

/*
Les seules fonctions que l'on va utiliser dans ce fichier sont les fonctions :
    - construire() :
        * en paramètre :
            ø un pointeur sur la structure jeu
            ø le type de la construction en utilisant les macros définies dans structure.h (ex : TYPE_ROUTE)
            ø la position du coin haut gauche de la construction (pos_x, pos_y)
            ø et si la construction est horizontale ou non (sert juste pour les cntrales et les chateau d'eau)
        * en sortie :
            ø 1 si la construction a été effectuée
            ø 0 si la construction n'a pas été effectuée (pas assez d'argent, pas assez de place, etc.)
    - detruire() : 
        * en paramètre :
            ø un pointeur sur la structure jeu
            ø le type de la construction en utilisant les macros définies dans structure.h (ex : TYPE_ROUTE)
            ø le numero de la construction à détruire pour les maisons, les centrales et les chateau d'eau
            ø la position (pos_x, pos_y) seulement pour les routes
        * en sortie :
            ø 1 si la destruction a été effectuée
            ø 0 si la destruction n'a pas été effectuée (construction inexistente, etc.)
Ces fonctions s'occupent automatiquement de remplir les listes d'adjacences et de "remplir" les cases de la map.
*/

/**************************************Construire***********************************************/

// sorties : 1 si ok sinon 0
bool batiment_sur_map(int pos_x, int pos_y, int taille_x, int taille_y);

bool check_argent(int argent_joueur, int argent_demande);

// Fonctions qui renvoient un tableau de position (indice 0 = x, indice 1 = y) des cases occupées par la construction 
// ou des cases adjacentes à la construction
int **detecter_cases_interieur(Jeu *jeu, int pos_x, int pos_y, int taille_x, int taille_y);

int **detecter_cases_adjacentes(Jeu *jeu, int pos_x, int pos_y, int taille_x, int taille_y, int *taille_tab);

// sortie : 1 si ok sinon 0
// on utilise le tableau sortie par detecter_cases_interieur()
bool pas_de_batiment_sur_position(Jeu *jeu, int **tableau_cases_interieurs, int taille_tab);

// on modifie les cases de la map
void mettre_cases_occupees(Jeu *jeu, int pos_x, int pos_y, int taille_x, int taille_y, char symbole, int numero);

// fonction qui retourne une listes des éléments adjacents à la construction
Liste *detecter_routes_adjacentes(Route *routes, int nb_routes, int **tableau_cases_adjacentes, int taille_tab);

Liste *detecter_maisons_adjacentes(Maison *maisons, int nb_maisons, int **tableau_cases_adjacentes, int taille_tab);

Liste *
detecter_batiements_adjacents(Batiment *batiments, int nb_batiments, int **tableau_cases_adjacentes, int taille_tab);

// renvoie un tableau des listes adjacentes données par les 3 fonctions précédentes (indice 0 = routes, indice 1 = maisons, indice 2 = batiments)
Liste **detecter_elements_adjacents(Jeu *jeu, int type, int pos_x, int pos_y, int taille_x, int taille_y);

// fonctions appelées par construire() suivant le type de construction
void construire_maison(Jeu *jeu, int pos_x, int pos_y, Liste **elements_adjacents);

void
construire_batiment(Jeu *jeu, int pos_x, int pos_y, int type_batiment, bool horizontal, Liste **elements_adjacents);

void construire_route(Jeu *jeu, int pos_x, int pos_y, Liste **elements_adjacents);

bool construire(Jeu *jeu, int type_batiment, int pos_x, int pos_y, bool horizontal);

/************************************Fin Construire*********************************************/

/***************************************Détruire***********************************************/

// fonction qui décrémente les numeros dans la liste donné (sert lorsqu'on détruit une construction)
void faire_moins_un_si_sup_num(Liste **liste, int numero);

// on modifie les cases de la map
void mettre_cases_inoccupees(Jeu *jeu, int **tableau_cases_interieurs, int taille_tab);

// fonction appelée par detruire() suivant le type de construction
bool detruire_maison(Jeu *jeu, int numero);
bool detruire_batiment(Jeu *jeu, int numero, int type_batiment);
bool detruire_route(Jeu *jeu, int pos_x, int pos_y);

bool detruire(Jeu *jeu, int type_batiment, int numero, int pos_x, int pos_y);

// pour determiner le numero du batiment a detruire en fonction de sa position
bool trouverNumero(Jeu *jeu, int type_batiment, int *numero, int colonne, int ligne);
/*************************************Fin Détruire*********************************************/

/**************************************Changement de Niveau************************************/
void choix_mode_jeu (Jeu *jeu);
void evolution_et_regression(Jeu* jeu,int nummaison);
void evolution_maison (Jeu *jeu, int nummaison);
void changement_type_maison(Jeu *jeu);
bool regression_type_maison(Jeu*jeu, int nummaison);

#endif