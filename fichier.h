//
// Created by Mona Lias on 11/3/22.
//

#ifndef MYBRANCH_FONCTIONS_H
#define MYBRANCH_FONCTIONS_H
#include <stdio.h>
#include "structure.h"
#include <stdbool.h>
#include <stdlib.h>
#include "affichage.h"
Case **chargerMap(Jeu * jeu);
void changerNiv(int *nivAct, Jeu * jeu);
void sauvegarderJeu(Jeu * jeu);
// fonctions pour permettre au joueur de choisir le type et l'emplacement de sa construction
char choixConstruction(char *type);
bool choixEmplacement(int *ligne, int *colonne, Jeu* jeu);
#endif //MYBRANCH_FONCTIONS_H
