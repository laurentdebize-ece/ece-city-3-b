#include "liste.h"
#include <stdlib.h>
#include <stdio.h>

void ajouter_liste (struct Liste** liste, int numero){

    struct Liste* new_item = (struct Liste*)malloc(sizeof(struct Liste));
    new_item->numero = numero;
    new_item->suivant = *liste;
    *liste = new_item;
}

void retirer_liste (struct Liste** liste, int numero){
    if (*liste != NULL){
        struct Liste* tmp = *liste; 
        if ((*liste)->numero == numero){
            *liste  = (*liste)->suivant;
            free(tmp);
        }
        else{
            while(tmp->suivant != NULL && tmp->suivant->numero != numero){
                tmp = tmp->suivant;
            }
            if (tmp->suivant != NULL){
                struct Liste* element_a_supprimer = tmp->suivant;
                tmp->suivant = element_a_supprimer->suivant;
                free(element_a_supprimer); 
            }
        }
    }
}

void free_liste (struct Liste** liste){
    struct Liste* tmp;
    while (*liste != NULL){
        tmp = *liste;
        *liste = (*liste)->suivant;
        free(tmp);
    }
}

void afficher_liste (struct Liste* liste){
    while (liste != NULL){
        printf("%d ", liste->numero);
        liste = liste->suivant;
    }
    printf("\n");
}

void enfiler (File** file, int numero){
    File * tmp = *file;
    File * new_item = (File*)malloc(sizeof(File));
    new_item->numero = numero;
    new_item->suivant = NULL;

    if (tmp == NULL){
        *file = new_item;
    }
    else{
        while (tmp->suivant != NULL){
            tmp = tmp->suivant;
        }
        tmp->suivant = new_item;
    }
}

int defiler (File** file){
    int numero = -1;
    if (*file != NULL){
        File * tmp = *file;
        numero = tmp->numero;
        *file = (*file)->suivant;
        free(tmp);
    }
    return numero;
}

void free_file (File** file){
    free_liste(file);
}