#include "construction_destruction.h"
#include <stdlib.h>

/**************************************Construire***********************************************/

bool check_argent(int argent_joueur, int argent_demande){
    return (argent_joueur >= argent_demande)? true : false;
}

int** detecter_cases_interieur(Jeu* jeu,int pos_x,int pos_y,int taille_x,int taille_y){
    int nb_cases = taille_x*taille_y;
    int** cases_interieurs = (int**)malloc(nb_cases*sizeof(int*));
    for (int i = 0; i < nb_cases; i++){
        cases_interieurs[i] = (int*)malloc(2*sizeof(int));
    }
    
    for (int i = 0; i < taille_x; i++){
        for (int j = 0; i < taille_y; i++){
            cases_interieurs[i*taille_x + j][0] = i + pos_x;
            cases_interieurs[i*taille_x + j][1] = j + pos_y;
        }
    }
    
    return cases_interieurs;
}

int** detecter_cases_adjacentes(Jeu* jeu,int pos_x,int pos_y,int taille_x,int taille_y){
    int nb_cases = 2*(taille_x + taille_y) + 4;
    int** cases_adjacentes = (int**)malloc(nb_cases*sizeof(int*));
    for (int i = 0; i < nb_cases; i++){
        cases_adjacentes[i] = (int*)malloc(2*sizeof(int));
    }

    int compteur_indice = 0;
    for (int i = 0; i < taille_x; i++){
        if (i == 0 || i == taille_x){
            for (int j = 0; i < taille_y; i++){
                cases_adjacentes[compteur_indice][0] = i + pos_x;
                cases_adjacentes[compteur_indice][1] = j + pos_y;
                compteur_indice++;
            }
        }
        else{
            cases_adjacentes[compteur_indice][0] = i + pos_x;
            cases_adjacentes[compteur_indice][1] = 0 + pos_y;
            compteur_indice++;
            cases_adjacentes[compteur_indice][0] = i + pos_x;
            cases_adjacentes[compteur_indice][1] = taille_y + pos_y;
            compteur_indice++;
        }
    }

    return cases_adjacentes;
}

bool pas_de_batiment_sur_position(Jeu* jeu,int** tableau_cases_interieurs,int taille_tab){
    for (int i = 0; i < taille_tab; i++){
        if(jeu->map[tableau_cases_interieurs[i][0]][tableau_cases_interieurs[i][1]].occupe)
            return false;
    }
    return true;
}

Liste* detecter_routes_adjacentes(Route* routes,int nb_routes,int** tableau_cases_adjacentes,int taille_tab){
    Liste* liste_routes_adjacentes = NULL;

    for (int i = 0; i < taille_tab; i++){
        for(int j = 0; j < nb_routes; j++){
            if(routes[j].pos_x == tableau_cases_adjacentes[i][0] && routes[j].pos_y == tableau_cases_adjacentes[i][1]){
                ajouter_liste(&liste_routes_adjacentes,j);
            }
        }
    }
    
    return liste_routes_adjacentes;
}


Liste* detecter_maisons_adjacentes(Maison* maisons,int nb_maisons,int** tableau_cases_adjacentes,int taille_tab){
    Liste* liste_maisons_adjacentes = NULL;

    for (int i = 0; i < taille_tab; i++){
        for(int j = 0; j < nb_maisons; j++){
            bool deja_ajoute = false;
            for (int k = 0; k < TAILLE_MAISON; k++){
                for (int l = 0; l < TAILLE_MAISON; l++){
                    if(!deja_ajoute && maisons[j].pos_x + k == tableau_cases_adjacentes[i][0] && maisons[j].pos_y + l == tableau_cases_adjacentes[i][1]){
                        ajouter_liste(&liste_maisons_adjacentes,j);
                        deja_ajoute = true;
                    }
                }   
            }
        }
    }
    
    return liste_maisons_adjacentes;
}


Liste* detecter_batiements_adjacents(Batiment* batiments,int nb_batiments,int** tableau_cases_adjacentes,int taille_tab){
    Liste* liste_batiments_adjacents = NULL;

    for(int j = 0; j < nb_batiments; j++){
        bool deja_ajoute = false;
        int taille_x = TAILLE_PETITE_BATIMENT, taille_y = TAILLE_GRANDE_BATIMENT;
        if (batiments[j].horizontal){
            taille_x = TAILLE_GRANDE_BATIMENT;
            taille_y = TAILLE_PETITE_BATIMENT;
        }

        for (int k = 0; k < taille_x; k++){
            for (int l = 0; l < taille_y; l++){
                for (int i = 0; i < taille_tab; i++){
                    if(!deja_ajoute && batiments[j].pos_x + k == tableau_cases_adjacentes[i][0] && batiments[j].pos_y + l == tableau_cases_adjacentes[i][1]){
                        ajouter_liste(&liste_batiments_adjacents,j);
                        deja_ajoute = true;
                    }
                }
            }   
        }
    }
    
    return liste_batiments_adjacents;
}


Liste** detecter_elements_adjacents(Jeu* jeu,int type,int pos_x,int pos_y,int taille_x,int taille_y){
    Liste** elements_adjacents = (Liste**)malloc(3*sizeof(Liste*));
    for (int i = 0; i < 3; i++){
        elements_adjacents[i] = NULL;
    }

    int** cases_adjacentes = detecter_cases_adjacentes(jeu,pos_x,pos_y,taille_x,taille_y);
    int taille_tab = 2*(taille_x + taille_y) + 4;
    
    if (type ==  TYPE_ROUTE){
        elements_adjacents[TYPE_ROUTE] = detecter_routes_adjacentes(jeu->routes,jeu->nb_routes,cases_adjacentes,taille_tab);
        elements_adjacents[TYPE_MAISON] = detecter_maisons_adjacentes(jeu->maisons,jeu->nb_maisons,cases_adjacentes,taille_tab);
        elements_adjacents[TYPE_BATIMENT] = detecter_batiements_adjacents(jeu->batiments,jeu->nb_centrales+jeu->nb_chateau_eau,cases_adjacentes,taille_tab);
    }
    else{
        elements_adjacents[TYPE_ROUTE] = detecter_routes_adjacentes(jeu->routes,jeu->nb_routes,cases_adjacentes,taille_tab);
    }

    for (int i = 0; i < taille_tab; i++){
        free(cases_adjacentes[i]);
    }
    free(cases_adjacentes);

    return elements_adjacents;
}

void construire_maison(Jeu* jeu,int pos_x,int pos_y,Liste** elements_adjacents){
    jeu->maisons[jeu->nb_maisons].pos_x = pos_x;
    jeu->maisons[jeu->nb_maisons].pos_y = pos_y;
    jeu->maisons[jeu->nb_maisons].routeAdjacente = elements_adjacents[TYPE_ROUTE];
    (jeu->nb_maisons)++;
}

void construire_batiment(Jeu* jeu,int pos_x,int pos_y,int type_batiment,bool horizontal,Liste** elements_adjacents){
    jeu->batiments[jeu->nb_centrales+jeu->nb_chateau_eau].pos_x = pos_x;
    jeu->batiments[jeu->nb_centrales+jeu->nb_chateau_eau].pos_y = pos_y;
    jeu->batiments[jeu->nb_centrales+jeu->nb_chateau_eau].routeAdjacente = elements_adjacents[TYPE_ROUTE];
    jeu->batiments[jeu->nb_centrales+jeu->nb_chateau_eau].capacite = CAPACITE_BATIMENTS;
    jeu->batiments[jeu->nb_centrales+jeu->nb_chateau_eau].horizontal = horizontal;
    jeu->batiments[jeu->nb_centrales+jeu->nb_chateau_eau].type_batiment = type_batiment;

    switch (type_batiment)
    {
    case TYPE_CENTRALE:
        (jeu->nb_centrales)++;
        break;
    case TYPE_CHATEAU_EAU:
        (jeu->nb_chateau_eau)++;
        break;
    }
}

void construire_route(Jeu* jeu,int pos_x,int pos_y,Liste** elements_adjacents){
    jeu->routes[jeu->nb_routes].pos_x = pos_x;
    jeu->routes[jeu->nb_routes].pos_y = pos_y;
    jeu->routes[jeu->nb_routes].adjacente_route = elements_adjacents[TYPE_ROUTE];
    jeu->routes[jeu->nb_routes].adjacente_maison = elements_adjacents[TYPE_MAISON];
    jeu->routes[jeu->nb_routes].adjacente_batiment = elements_adjacents[TYPE_BATIMENT];
    (jeu->nb_routes)++;
}

bool construire(Jeu* jeu,int type_batiment,int pos_x,int pos_y,bool horizontal){
    int argent_demande;
    int type;
    int taille_x,taille_y;
    switch (type_batiment)
    {
    case TYPE_ROUTE:
        argent_demande = PRIX_ROUTE;
        type = TYPE_ROUTE;
        taille_x = 1;
        taille_y = 1;
        break;
    case TYPE_MAISON:
        argent_demande = PRIX_MAISON;
        type = TYPE_MAISON;
        taille_x = TAILLE_MAISON;
        taille_y = TAILLE_MAISON;
        break;
    case TYPE_CENTRALE:
        argent_demande = PRIX_CENTRALE;
        type = TYPE_BATIMENT;
        taille_x = TAILLE_PETITE_BATIMENT;
        taille_y = TAILLE_GRANDE_BATIMENT;
        if (horizontal){
            taille_x = TAILLE_GRANDE_BATIMENT;
            taille_y = TAILLE_PETITE_BATIMENT;
        }
        break;
    case TYPE_CHATEAU_EAU:
        argent_demande = PRIX_CHATEAU_EAU;
        type = TYPE_BATIMENT;
        taille_x = TAILLE_PETITE_BATIMENT;
        taille_y = TAILLE_GRANDE_BATIMENT;
        if (horizontal){
            taille_x = TAILLE_GRANDE_BATIMENT;
            taille_y = TAILLE_PETITE_BATIMENT;
        }
        break;
    default:
        return false;
        break;
    }

    if (check_argent(jeu->argent,argent_demande)){
        int** cases_interieur = detecter_cases_interieur(jeu,pos_x,pos_y,taille_x,taille_y);
        if (pas_de_batiment_sur_position(jeu,cases_interieur,taille_x*taille_y)){
            Liste** elements_adjacents = detecter_elements_adjacents(jeu,type,pos_x,pos_y,taille_x,taille_y);

            switch (type)
            {
            case TYPE_ROUTE:
                construire_route(jeu,pos_x,pos_y,elements_adjacents);
                break;
            case TYPE_MAISON:
                construire_maison(jeu,pos_x,pos_y,elements_adjacents);
                break;
            case TYPE_BATIMENT:
                construire_batiment(jeu,pos_x,pos_y,type_batiment,horizontal,elements_adjacents);
                break;
            }

            for (int i = 0; i < taille_x*taille_y; i++){
                free(cases_interieur[i]);
            }
            free(cases_interieur);
        }
        else
            for (int i = 0; i < taille_x*taille_y; i++){
                free(cases_interieur[i]);
            }
            free(cases_interieur);
            return false;
    }
    else
        return false;
    return true;
}

/************************************Fin Construire*********************************************/

/***************************************Détruire***********************************************/

void faire_moins_un_si_sup_num(Liste** liste,int numero){
    if (*liste != NULL){
        struct Liste* tmp = *liste; 
        while(tmp!=NULL){
            if(tmp->numero > numero)
                (tmp->numero)--;
        }
    }
}

bool detruire_maison(Jeu* jeu, int numero){
    if(numero < jeu->nb_maisons){
        for (int i = 0; i < jeu->nb_routes; i++){
            retirer_liste(&(jeu->routes[i].adjacente_maison),numero);
            faire_moins_un_si_sup_num(&(jeu->routes[i].adjacente_maison),numero);
        }
        free_liste(&(jeu->maisons[numero].routeAdjacente));
        for (int i = numero; i < jeu->nb_maisons; i++){
            jeu->maisons[i].eau = jeu->maisons[i+1].eau;
            jeu->maisons[i].electricite = jeu->maisons[i+1].electricite;
            jeu->maisons[i].habitants = jeu->maisons[i+1].habitants;
            jeu->maisons[i].niveau = jeu->maisons[i+1].niveau;
            jeu->maisons[i].pos_x = jeu->maisons[i+1].pos_x;
            jeu->maisons[i].pos_y = jeu->maisons[i+1].pos_y;
            jeu->maisons[i].routeAdjacente = jeu->maisons[i+1].routeAdjacente;
        }

        (jeu->nb_maisons)--;
        
        return true;
    }
    return false;
}

bool detruire_batiment(Jeu* jeu, int numero,int type_batiment){
    if(numero < jeu->nb_centrales+jeu->nb_chateau_eau){
        for (int i = 0; i < jeu->nb_centrales+jeu->nb_chateau_eau; i++){
            retirer_liste(&(jeu->routes[i].adjacente_batiment),numero);
            faire_moins_un_si_sup_num(&(jeu->routes[i].adjacente_batiment),numero);
        }
        free_liste(&(jeu->batiments[numero].routeAdjacente));
        for (int i = numero; i < jeu->nb_centrales+jeu->nb_chateau_eau; i++){
            jeu->batiments[i].capacite = jeu->batiments[i+1].capacite;
            jeu->batiments[i].horizontal = jeu->batiments[i+1].horizontal;
            jeu->batiments[i].pos_x = jeu->batiments[i+1].pos_x;
            jeu->batiments[i].pos_y = jeu->batiments[i+1].pos_y;
            jeu->batiments[i].routeAdjacente = jeu->batiments[i+1].routeAdjacente;
        }
        
        switch(type_batiment){
            case TYPE_CENTRALE:
                (jeu->nb_centrales)--;
                break;
            case TYPE_CHATEAU_EAU:
                (jeu->nb_chateau_eau)--;
                break;
        }

        return true;
    }
    return false;
}

bool detruire_route(Jeu* jeu, int pos_x,int pos_y){
    for (int i = 0; i < jeu->nb_routes; i++){
        if (jeu->routes[i].pos_x == pos_x && jeu->routes[i].pos_y == pos_y){
            for (int j = 0; j < jeu->nb_routes; j++){
                retirer_liste(&(jeu->routes[i].adjacente_maison),i);
                faire_moins_un_si_sup_num(&(jeu->routes[i].adjacente_maison),i);
            }
            for (int j = 0; j < jeu->nb_maisons; j++){
                retirer_liste(&(jeu->maisons[i].routeAdjacente),i);
                faire_moins_un_si_sup_num(&(jeu->maisons[i].routeAdjacente),i);
            }
            for (int j = 0; j < jeu->nb_centrales+jeu->nb_chateau_eau; j++){
                retirer_liste(&(jeu->batiments[i].routeAdjacente),i);
                faire_moins_un_si_sup_num(&(jeu->batiments[i].routeAdjacente),i);
            }
            free_liste(&(jeu->routes[i].adjacente_maison));
            free_liste(&(jeu->routes[i].adjacente_batiment));
            free_liste(&(jeu->routes[i].adjacente_route));

            for (int j = i; j < jeu->nb_routes; j++){
                jeu->routes[j].adjacente_batiment = jeu->routes[j+1].adjacente_batiment;
                jeu->routes[j].adjacente_maison = jeu->routes[j+1].adjacente_maison;
                jeu->routes[j].adjacente_route = jeu->routes[j+1].adjacente_route;
                jeu->routes[j].pos_x = jeu->routes[j+1].pos_x;
                jeu->routes[j].pos_y = jeu->routes[j+1].pos_y;
            }

            (jeu->nb_routes)--;

            return true;
        }
    }

    return false;
}

bool detruire(Jeu* jeu, int type_batiment, int numero,int pos_x,int pos_y){
    switch (type_batiment)
    {
    case TYPE_ROUTE:
        if(detruire_route(jeu,pos_x,pos_y))
            return true;
        break;
    case TYPE_MAISON:
        if(detruire_maison(jeu,numero))
            return true;
        break;
    case TYPE_CENTRALE:
        if(detruire_batiment(jeu,numero,type_batiment))
            return true;
        break;
    case TYPE_CHATEAU_EAU:
        if(detruire_batiment(jeu,numero,type_batiment))
    default:
        break;
    }
    return false;
}

/*************************************Fin Détruire*********************************************/