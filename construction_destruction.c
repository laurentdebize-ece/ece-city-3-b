#include "construction_destruction.h"
#include "debug.h"
#include "compteur.h"
#include "eau.h"
#include "elec.h"
#include <stdlib.h>

/**************************************Construire***********************************************/

bool batiment_sur_map(int pos_x, int pos_y, int taille_x, int taille_y){
    if(pos_x + taille_x - 1 >= TAILLE_MAP_X || pos_y + taille_y - 1 >= TAILLE_MAP_Y || pos_x < 0 || pos_y < 0){
        return false;
    }
    return true;
}

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
        for (int j = 0; j < taille_y; j++){
            cases_interieurs[i*taille_y + j][0] = i + pos_x;
            cases_interieurs[i*taille_y + j][1] = j + pos_y;
        }
    }
    return cases_interieurs;
}

// macros pour savoir si la construction est sur un ou plusieurs bords de la map
// <=> la construction n'a pas d'éléments adjacents de ce coté là
#define PAS_ELEMENTS_A_GAUCHE 2
#define PAS_ELEMENTS_A_DROITE 3
#define PAS_ELEMENTS_EN_HAUT 5
#define PAS_ELEMENTS_EN_BAS 7
int** detecter_cases_adjacentes(Jeu* jeu,int pos_x,int pos_y,int taille_x,int taille_y,int* taille_tab){

    int pas_element = 1;
    if (pos_x == 0){
        pas_element *= PAS_ELEMENTS_A_GAUCHE;
    }
    if (pos_x + taille_x == TAILLE_MAP_X){
        pas_element *= PAS_ELEMENTS_A_DROITE;
    }
    if (pos_y == 0){
        pas_element *= PAS_ELEMENTS_EN_HAUT;
    }
    if (pos_y + taille_y == TAILLE_MAP_Y){
        pas_element *= PAS_ELEMENTS_EN_BAS;
    }

    // on détermine le nombre de cases adjacentes dans *taille_tab
    if (((pas_element%PAS_ELEMENTS_A_GAUCHE == 0)&&(pas_element%PAS_ELEMENTS_EN_HAUT == 0))
        ||((pas_element%PAS_ELEMENTS_A_GAUCHE == 0)&&(pas_element%PAS_ELEMENTS_EN_BAS == 0))
        ||((pas_element%PAS_ELEMENTS_A_DROITE == 0)&&(pas_element%PAS_ELEMENTS_EN_HAUT == 0))
        ||((pas_element%PAS_ELEMENTS_A_DROITE == 0)&&(pas_element%PAS_ELEMENTS_EN_BAS == 0))){
        *taille_tab = taille_x + taille_y;
    }
    else if ((pas_element%PAS_ELEMENTS_A_GAUCHE == 0)||(pas_element%PAS_ELEMENTS_A_DROITE == 0)){
        *taille_tab = 2*taille_x + taille_y;
    }
    else if ((pas_element%PAS_ELEMENTS_EN_HAUT == 0)||(pas_element%PAS_ELEMENTS_EN_BAS == 0)){
        *taille_tab = 2*taille_y + taille_x;
    }
    else{
        *taille_tab = 2*taille_x + 2*taille_y;
    }

    int** cases_adjacentes = (int**)malloc((*taille_tab)*sizeof(int*));
    for (int i = 0; i < *taille_tab; i++){
        cases_adjacentes[i] = (int*)malloc(2*sizeof(int));
    }

    // on remplit le tableau de cases adjacentes selon les cas
    int compteur_indice = 0;
    if (!(pas_element%PAS_ELEMENTS_A_GAUCHE == 0)){
        for (int i = 0; i < taille_y; i++){
            cases_adjacentes[compteur_indice][0] = pos_x - 1;
            cases_adjacentes[compteur_indice][1] = pos_y + i;
            compteur_indice++;
        }
    }
    if (!(pas_element%PAS_ELEMENTS_A_DROITE == 0)){
        for (int i = 0; i < taille_y; i++){
            cases_adjacentes[compteur_indice][0] = pos_x + taille_x;
            cases_adjacentes[compteur_indice][1] = pos_y + i;
            compteur_indice++;
        }
    }
    if (!(pas_element%PAS_ELEMENTS_EN_HAUT == 0)){
        for (int i = 0; i < taille_x; i++){
            cases_adjacentes[compteur_indice][0] = pos_x + i;
            cases_adjacentes[compteur_indice][1] = pos_y - 1;
            compteur_indice++;
        }
    }
    if (!(pas_element%PAS_ELEMENTS_EN_BAS == 0)){
        for (int i = 0; i < taille_x; i++){
            cases_adjacentes[compteur_indice][0] = pos_x + i;
            cases_adjacentes[compteur_indice][1] = pos_y + taille_y;
            compteur_indice++;
        }
    }

    return cases_adjacentes;
}

bool pas_de_batiment_sur_position(Jeu* jeu,int** tableau_cases_interieurs,int taille_tab){
    for (int i = 0; i < taille_tab; i++){
        // O <=> x et 1 <=> y
        if(jeu->map[tableau_cases_interieurs[i][0]][tableau_cases_interieurs[i][1]].occupe)
            return false;
    }
    return true;
}

void mettre_cases_occupees(Jeu* jeu,int pos_x,int pos_y,int taille_x,int taille_y,char symbole,int numero){
    for (int i = 0; i < taille_x; i++){
        for (int j = 0; j < taille_y; j++){
            jeu->map[pos_x + i][pos_y + j].occupe = true;
            // sur les bords de la construction on met le symbole de la construction et à l'intérieur le numéro de la construction
            if (i == 0 || i == taille_x - 1 || j == 0 || j == taille_y - 1){
                jeu->map[pos_x + i][pos_y + j].symbole = symbole;
            }
            else{
                jeu->map[pos_x + i][pos_y + j].symbole = '0'+numero;
            }
        }
    }
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
    
    int taille_tab;
    int** cases_adjacentes = detecter_cases_adjacentes(jeu,pos_x,pos_y,taille_x,taille_y,&taille_tab);
    
    // les routes ont une liste d'ajdacences pour les maisons, les batiments et les routes
    if (type ==  TYPE_ROUTE){
        elements_adjacents[TYPE_ROUTE] = detecter_routes_adjacentes(jeu->routes,jeu->nb_routes,cases_adjacentes,taille_tab);
        elements_adjacents[TYPE_MAISON] = detecter_maisons_adjacentes(jeu->maisons,jeu->nb_maisons,cases_adjacentes,taille_tab);
        elements_adjacents[TYPE_BATIMENT] = detecter_batiements_adjacents(jeu->batiments,jeu->nb_centrales+jeu->nb_chateau_eau,cases_adjacentes,taille_tab);
    }
    else{// alors que les batiments et les maisons n'ont que des listes d'adjacences pour les routes
        elements_adjacents[TYPE_ROUTE] = detecter_routes_adjacentes(jeu->routes,jeu->nb_routes,cases_adjacentes,taille_tab);
    }

    for (int i = 0; i < taille_tab; i++){
        free(cases_adjacentes[i]);
    }
    free(cases_adjacentes);

    return elements_adjacents;
}

void construire_maison(Jeu* jeu,int pos_x,int pos_y,Liste** elements_adjacents){
    // on ajoute la maison au tableau de maisons au premier emplacement libre
    jeu->maisons[jeu->nb_maisons].pos_x = pos_x;
    jeu->maisons[jeu->nb_maisons].pos_y = pos_y;
    jeu->maisons[jeu->nb_maisons].routeAdjacente = elements_adjacents[TYPE_ROUTE];
    jeu->maisons[jeu->nb_maisons].timer=0;
    Liste* tmp = jeu->maisons[jeu->nb_maisons].routeAdjacente;
    while(tmp != NULL){
        // comme les graphes sont non orienté on ajoute la maison à la liste d'adjacence de toute les route de sa liste
        ajouter_liste(&jeu->routes[tmp->numero].adjacente_maison,jeu->nb_maisons);
        tmp = tmp->suivant;
    }
    (jeu->nb_maisons)++;
}

void construire_batiment(Jeu* jeu,int pos_x,int pos_y,int type_batiment,bool horizontal,Liste** elements_adjacents){
    // même principe que pour les maisons
    jeu->batiments[jeu->nb_centrales+jeu->nb_chateau_eau].pos_x = pos_x;
    jeu->batiments[jeu->nb_centrales+jeu->nb_chateau_eau].pos_y = pos_y;
    jeu->batiments[jeu->nb_centrales+jeu->nb_chateau_eau].routeAdjacente = elements_adjacents[TYPE_ROUTE];
    Liste* tmp = jeu->batiments[jeu->nb_centrales+jeu->nb_chateau_eau].routeAdjacente;
    while(tmp != NULL){
        ajouter_liste(&(jeu->routes[tmp->numero].adjacente_batiment),jeu->nb_centrales+jeu->nb_chateau_eau);
        tmp = tmp->suivant;
    }
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
    // même principe que pour les maisons et les batiments
    jeu->routes[jeu->nb_routes].pos_x = pos_x;
    jeu->routes[jeu->nb_routes].pos_y = pos_y;
    jeu->routes[jeu->nb_routes].adjacente_route = elements_adjacents[TYPE_ROUTE];
    Liste* tmp = jeu->routes[jeu->nb_routes].adjacente_route;
    while (tmp != NULL){
        ajouter_liste(&(jeu->routes[tmp->numero].adjacente_route),jeu->nb_routes);
        tmp = tmp->suivant;
    }
    jeu->routes[jeu->nb_routes].adjacente_maison = elements_adjacents[TYPE_MAISON];
    tmp = jeu->routes[jeu->nb_routes].adjacente_maison;
    while (tmp != NULL){
        ajouter_liste(&(jeu->maisons[tmp->numero].routeAdjacente),jeu->nb_routes);
        tmp = tmp->suivant;
    }
    jeu->routes[jeu->nb_routes].adjacente_batiment = elements_adjacents[TYPE_BATIMENT];
    tmp = jeu->routes[jeu->nb_routes].adjacente_batiment;
    while (tmp != NULL){
        ajouter_liste(&(jeu->batiments[tmp->numero].routeAdjacente),jeu->nb_routes);
        tmp = tmp->suivant;
    }
    (jeu->nb_routes)++;
}

bool construire(Jeu* jeu,int type_batiment,int pos_x,int pos_y,bool horizontal){
    int argent_demande;
    int type;
    int taille_x,taille_y;
    char symbole;
    int numero;
    // determine les différentes variables ci-dessus en fonction du type de batiment
    switch (type_batiment)
    {
    case TYPE_ROUTE:
        argent_demande = PRIX_ROUTE;
        type = TYPE_ROUTE;
        taille_x = 1;
        taille_y = 1;
        symbole = SYMBOLE_ROUTE;
        numero = jeu->nb_routes;
        break;
    case TYPE_MAISON:
        argent_demande = PRIX_MAISON;
        type = TYPE_MAISON;
        taille_x = TAILLE_MAISON;
        taille_y = TAILLE_MAISON;
        symbole = SYMBOLE_MAISON;
        numero = jeu->nb_maisons;
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
        symbole = SYMBOLE_CENTRALE;
        numero = jeu->nb_centrales+jeu->nb_chateau_eau;
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
        symbole = SYMBOLE_CHATEAU_EAU;
        numero = jeu->nb_centrales+jeu->nb_chateau_eau;
        break;
    default:
        // donc si le type de batiment n'est pas reconnu
        return false;
        break;
    }

    // on teste d'abord si le batiment est sur la carte et ensuite si on a assez d'argent
    if (batiment_sur_map(pos_x,pos_y,taille_x,taille_y) && check_argent(jeu->argent,argent_demande)){
        int** cases_interieur = detecter_cases_interieur(jeu,pos_x,pos_y,taille_x,taille_y);
        // on teste si les cases ou l'on va construire sont vides
        if (pas_de_batiment_sur_position(jeu,cases_interieur,taille_x*taille_y)){
            Liste** elements_adjacents = detecter_elements_adjacents(jeu,type,pos_x,pos_y,taille_x,taille_y);

            // on construit
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

            mettre_cases_occupees(jeu,pos_x,pos_y,taille_x,taille_y,symbole,numero);
            for (int i = 0; i < taille_x*taille_y; i++){
                free(cases_interieur[i]);
            }
            free(cases_interieur);

        }
        else{
            for (int i = 0; i < taille_x*taille_y; i++){
                free(cases_interieur[i]);
            }
            free(cases_interieur);
            return false;
        }
    }
    else
        return false;
    // si tout s'est bien passé on enlève l'argent de la banque
    jeu->argent -= argent_demande;
    return true;
}

/************************************Fin Construire*********************************************/

/***************************************Détruire***********************************************/

void faire_moins_un_si_sup_num(Liste** liste,int numero){
    if (*liste != NULL){
        Liste* tmp = *liste; 
        while(tmp!=NULL){
            if(tmp->numero > numero){
                (tmp->numero)--;
            }
            tmp = tmp->suivant;
        }
    }
}

void mettre_cases_inoccupees(Jeu* jeu,int** tableau_cases_interieurs,int taille_tab){
    for (int i = 0; i < taille_tab; i++){
        jeu->map[tableau_cases_interieurs[i][0]][tableau_cases_interieurs[i][1]].occupe = false;
        jeu->map[tableau_cases_interieurs[i][0]][tableau_cases_interieurs[i][1]].symbole = SYMBOLE_VIDE;
    }
}


bool detruire_maison(Jeu* jeu, int numero){
    // on retire la maison de toutes les listes d'adjacence
    for (int i = 0; i < jeu->nb_routes; i++){
        retirer_liste(&(jeu->routes[i].adjacente_maison),numero);
        // on fait -1 à tous les numéros supérieurs à celui de la maison à détruire car on décale toutes les maisons
        faire_moins_un_si_sup_num(&(jeu->routes[i].adjacente_maison),numero);
    }
    free_liste(&(jeu->maisons[numero].routeAdjacente));
    // on décale toutes les maisons après celle qu'on détruit
    for (int i = numero; i < jeu->nb_maisons; i++){
        jeu->maisons[i].eau = jeu->maisons[i+1].eau;
        jeu->maisons[i].electricite = jeu->maisons[i+1].electricite;
        jeu->maisons[i].habitants = jeu->maisons[i+1].habitants;
        jeu->maisons[i].niveau = jeu->maisons[i+1].niveau;
        jeu->maisons[i].pos_x = jeu->maisons[i+1].pos_x;
        jeu->maisons[i].pos_y = jeu->maisons[i+1].pos_y;
        jeu->maisons[i].routeAdjacente = jeu->maisons[i+1].routeAdjacente;
        jeu->maisons[i].position.pos_x = jeu->maisons[i+1].position.pos_x;
        jeu->maisons[i].position.pos_y = jeu->maisons[i+1].position.pos_y;
        jeu->maisons[i].position.pos_z = jeu->maisons[i+1].position.pos_z;
        if (i != jeu->nb_maisons-1){
            // pour modifier les indices dans l'affichage car on décale toutes les maisons
            mettre_cases_occupees(jeu,jeu->maisons[i].pos_x,jeu->maisons[i].pos_y,TAILLE_MAISON,TAILLE_MAISON,SYMBOLE_MAISON,i);
        }
    }

    (jeu->nb_maisons)--;
    
    return true;
}

bool detruire_batiment(Jeu* jeu, int numero,int type_batiment){
    // même principe que pour les maisons
    for (int i = 0; i < jeu->nb_routes; i++){
        retirer_liste(&(jeu->routes[i].adjacente_batiment),numero);
        faire_moins_un_si_sup_num(&(jeu->routes[i].adjacente_batiment),numero);
    }
    free_liste(&(jeu->batiments[numero].routeAdjacente));
    for (int i = numero; i < jeu->nb_centrales+jeu->nb_chateau_eau; i++){
        jeu->batiments[i].capacite = jeu->batiments[i+1].capacite;
        jeu->batiments[i].horizontal = jeu->batiments[i+1].horizontal;
        jeu->batiments[i].pos_x = jeu->batiments[i+1].pos_x;
        jeu->batiments[i].pos_y = jeu->batiments[i+1].pos_y;
        jeu->batiments[i].type_batiment = jeu->batiments[i+1].type_batiment;
        jeu->batiments[i].routeAdjacente = jeu->batiments[i+1].routeAdjacente;
        jeu->batiments[i].position.pos_x = jeu->batiments[i+1].position.pos_x;
        jeu->batiments[i].position.pos_y = jeu->batiments[i+1].position.pos_y;
        jeu->batiments[i].position.pos_z = jeu->batiments[i+1].position.pos_z;
        if (i != jeu->nb_centrales+jeu->nb_chateau_eau-1){
            mettre_cases_occupees(jeu,jeu->batiments[i].pos_x,jeu->batiments[i].pos_y,
            (jeu->batiments[i].horizontal)?TAILLE_GRANDE_BATIMENT:TAILLE_PETITE_BATIMENT,
            (jeu->batiments[i].horizontal?TAILLE_PETITE_BATIMENT:TAILLE_GRANDE_BATIMENT),
            jeu->map[jeu->batiments[i].pos_x][jeu->batiments[i].pos_y].symbole,i);
        }
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

bool detruire_route(Jeu* jeu, int numero){
    // même principe que pour les maisons et les batiments mais on a pas besoin de remodifier la carte
    for (int j = 0; j < jeu->nb_routes; j++){
        retirer_liste(&(jeu->routes[j].adjacente_route),numero);
        faire_moins_un_si_sup_num(&(jeu->routes[j].adjacente_route),numero);
    }
    for (int j = 0; j < jeu->nb_maisons; j++){
        retirer_liste(&(jeu->maisons[j].routeAdjacente),numero);
        faire_moins_un_si_sup_num(&(jeu->maisons[j].routeAdjacente),numero);
    }
    for (int j = 0; j < jeu->nb_centrales+jeu->nb_chateau_eau; j++){
        retirer_liste(&(jeu->batiments[j].routeAdjacente),numero);
        faire_moins_un_si_sup_num(&(jeu->batiments[j].routeAdjacente),numero);
    }
    free_liste(&(jeu->routes[numero].adjacente_maison));
    free_liste(&(jeu->routes[numero].adjacente_batiment));
    free_liste(&(jeu->routes[numero].adjacente_route));

    for (int j = numero; j < jeu->nb_routes; j++){
        jeu->routes[j].adjacente_batiment = jeu->routes[j+1].adjacente_batiment;
        jeu->routes[j].adjacente_maison = jeu->routes[j+1].adjacente_maison;
        jeu->routes[j].adjacente_route = jeu->routes[j+1].adjacente_route;
        jeu->routes[j].pos_x = jeu->routes[j+1].pos_x;
        jeu->routes[j].pos_y = jeu->routes[j+1].pos_y;
        jeu->routes[j].position.pos_x = jeu->routes[j+1].position.pos_x;
        jeu->routes[j].position.pos_y = jeu->routes[j+1].position.pos_y;
        jeu->routes[j].position.pos_z = jeu->routes[j+1].position.pos_z;
    }

    (jeu->nb_routes)--;

    return true;
}

bool detruire(Jeu* jeu,int pos_x,int pos_y){
    int numero,type_batiment;
    if(!trouverNumero_et_TypeBatiment(jeu,&type_batiment,&numero,pos_x,pos_y))
        return false;

    int taille_x, taille_y;
    switch (type_batiment)
    {
    case TYPE_ROUTE:
        taille_x = 1;
        taille_y = 1;
        if(!detruire_route(jeu,numero))
            return false;
        break;
    case TYPE_MAISON:
        // on vérifie que la maison existe
        if(numero >= 0 && numero < jeu->nb_maisons){
            taille_x = TAILLE_MAISON;
            taille_y = TAILLE_MAISON;
            pos_x = jeu->maisons[numero].pos_x;
            pos_y = jeu->maisons[numero].pos_y;
            if(!detruire_maison(jeu,numero))
                return false;
        }
        else
            return false;
        break;
    case TYPE_CENTRALE:
        // on vérifie que la centrale existe
        if (numero >= 0 && numero < jeu->nb_centrales+jeu->nb_chateau_eau && jeu->batiments[numero].type_batiment==TYPE_CENTRALE){
            taille_x = TAILLE_PETITE_BATIMENT;
            taille_y = TAILLE_GRANDE_BATIMENT;
            if(jeu->batiments[numero].horizontal){
                taille_x = TAILLE_GRANDE_BATIMENT;
                taille_y = TAILLE_PETITE_BATIMENT;
            }
            pos_x = jeu->batiments[numero].pos_x;
            pos_y = jeu->batiments[numero].pos_y;
            if(!detruire_batiment(jeu,numero,type_batiment))
                return false;
        }
        else
            return false;
        break;
    case TYPE_CHATEAU_EAU:
        // on vérifie que le chateau d'eau existe
        if (numero >= 0 && numero < jeu->nb_centrales+jeu->nb_chateau_eau && jeu->batiments[numero].type_batiment==TYPE_CHATEAU_EAU){
            taille_x = TAILLE_PETITE_BATIMENT;
            taille_y = TAILLE_GRANDE_BATIMENT;
            if(jeu->batiments[numero].horizontal){
                taille_x = TAILLE_GRANDE_BATIMENT;
                taille_y = TAILLE_PETITE_BATIMENT;
            }
            pos_x = jeu->batiments[numero].pos_x;
            pos_y = jeu->batiments[numero].pos_y;
            if(!detruire_batiment(jeu,numero,type_batiment))
                return false;
        }
        else
            return false;
        break;
    default:
        return false;
        break;
    }

    // on modifie la carte
    int** cases_interieurs = detecter_cases_interieur(jeu,pos_x,pos_y,taille_x,taille_y);
    mettre_cases_inoccupees(jeu,cases_interieurs,taille_x*taille_y);
    for(int i = 0; i < taille_x*taille_y; i++){
        free(cases_interieurs[i]);
    }
    free(cases_interieurs);

    return true;
}

// pour determiner le numero du batiment a detruire en fonction de sa position
bool trouverNumero_et_TypeBatiment(Jeu *jeu, int* type_batiment, int *numero, int colonne, int ligne) {
    for(int i = 0; i < jeu->nb_maisons; i++){
        if (colonne >= jeu->maisons[i].pos_x && colonne < jeu->maisons[i].pos_x + TAILLE_MAISON 
            && ligne >= jeu->maisons[i].pos_y && ligne < jeu->maisons[i].pos_y + TAILLE_MAISON){
            *type_batiment = TYPE_MAISON;
            *numero = i;
            return true;
        }
    }
    for(int i = 0;i<jeu->nb_routes;i++){
        if (colonne == jeu->routes[i].pos_x && ligne == jeu->routes[i].pos_y){
            *type_batiment = TYPE_ROUTE;
            *numero = i;
            return true;
        }
    }
    for(int i = 0;i<jeu->nb_centrales+jeu->nb_chateau_eau;i++){
        if (jeu->batiments[i].horizontal){
            if (colonne >= jeu->batiments[i].pos_x && colonne < jeu->batiments[i].pos_x + TAILLE_GRANDE_BATIMENT 
                && ligne >= jeu->batiments[i].pos_y && ligne < jeu->batiments[i].pos_y + TAILLE_PETITE_BATIMENT){
                *type_batiment = jeu->batiments[i].type_batiment;
                *numero = i;
                return true;
            }
        }
        else{
            if (colonne >= jeu->batiments[i].pos_x && colonne < jeu->batiments[i].pos_x + TAILLE_PETITE_BATIMENT 
                && ligne >= jeu->batiments[i].pos_y && ligne < jeu->batiments[i].pos_y + TAILLE_GRANDE_BATIMENT){
                *type_batiment = jeu->batiments[i].type_batiment;
                *numero = i;
                return true;
            }
        }
    }
    return false;
}
/*************************************Fin Détruire*********************************************/

/*************************************Changement de Niveau*************************************/

void choix_mode_jeu (Jeu *jeu) {
    printf("Choisissez le mode de jeu : \n 1- Mode capitaliste\n 2- Mode communiste\n");
    scanf("%d",&jeu->mode_jeu);
}

void evolution_et_regression(Jeu* jeu,int nummaison){
        if (!regression_type_maison(jeu,nummaison)){
            evolution_maison(jeu,nummaison);
        }
}

void evolution_maison(Jeu* jeu, int nummaison){
    int ancien_nb_hab = jeu->maisons[nummaison].habitants;
    switch (jeu->mode_jeu) {
        case MODE_CAPITALISTE:
                if(jeu->maisons[nummaison].niveau<=NIVEAU_IMMEUBLE){
                    jeu->maisons[nummaison].niveau++;
                    maj_totale(jeu);
                    if (jeu->maisons[nummaison].habitants == 0){
                        jeu->maisons[nummaison].niveau--;
                    }
                }
            break;
        case MODE_COMMUNISTE:
                switch (jeu->maisons[nummaison].niveau) {
                    case NIVEAU_TERRAIN_VAGUE:
                        if (jeu->maisons[nummaison].habitants>= 0) {
                            jeu->maisons[nummaison].niveau=NIVEAU_CABANE;
                            maj_totale(jeu);
                            if (jeu->maisons[nummaison].habitants == 0){
                                jeu->maisons[nummaison].niveau--;
                            }
                        }
                        break;
                        
                    case NIVEAU_CABANE:
                        if (jeu->maisons[nummaison].habitants>= HAB_MAX_CABANE) {
                            jeu->maisons[nummaison].niveau=NIVEAU_MAISON;
                            maj_totale(jeu);
                            if (jeu->maisons[nummaison].habitants <= ancien_nb_hab){
                                jeu->maisons[nummaison].niveau--;
                            }
                        }
                        break;
                    case NIVEAU_MAISON:
                        if (jeu->maisons[nummaison].habitants>= HAB_MAX_MAISON && jeu->eau>0 && jeu->electricite>HAB_MAX_IMMEUBLE) {
                            jeu->maisons[nummaison].niveau=NIVEAU_IMMEUBLE;
                            maj_totale(jeu);
                            if (jeu->maisons[nummaison].habitants <= ancien_nb_hab){
                                jeu->maisons[nummaison].niveau--;
                            }
                        }
                        break;
                    case NIVEAU_IMMEUBLE:
                        if (jeu->maisons[nummaison].habitants>= HAB_MAX_IMMEUBLE && jeu->eau>0 && jeu->electricite>HAB_MAX_GRATTE_CIEL) {
                            jeu->maisons[nummaison].niveau=NIVEAU_GRATTE_CIEL;
                            maj_totale(jeu);
                            if (jeu->maisons[nummaison].habitants <= ancien_nb_hab){
                                jeu->maisons[nummaison].niveau--;
                            }
                        }
                        break;
                    default:
                        break;
                }
            break;
        default:
            break;
    }

}


bool regression_type_maison(Jeu*jeu, int nummaison){
        switch (jeu->maisons[nummaison].niveau) {
            case NIVEAU_CABANE:
                if (jeu->maisons[nummaison].habitants == 0) {
                    jeu->maisons[nummaison].niveau=NIVEAU_RUINE;
                    return 1;
                    break;
                }
            case NIVEAU_MAISON:
                if (jeu->maisons[nummaison].habitants< NIVEAU_CABANE) {
                    jeu->maisons[nummaison].niveau=NIVEAU_CABANE;
                    return 1;
                    break;
                }
            case NIVEAU_IMMEUBLE:
                if (jeu->maisons[nummaison].habitants< NIVEAU_MAISON) {
                    jeu->maisons[nummaison].niveau=NIVEAU_MAISON;
                    return 1;
                    break;
                }
            case NIVEAU_GRATTE_CIEL:
                if (jeu->maisons[nummaison].habitants< HAB_MAX_IMMEUBLE) {
                    jeu->maisons[nummaison].niveau=NIVEAU_IMMEUBLE;
                    return 1;
                    break;
                }
            default:
                break;

        }
        return 0;
}

void maj_totale(Jeu *jeu) {
    repartitionEau(jeu);
    repartition_electricite(jeu);
    repartition_habitants(jeu);
    maj_compteurs(jeu);
}

void detection_temps(Jeu *jeu) {
    time_t temps = time(NULL);
    if (jeu->temps != temps) {
        jeu->temps = temps;
        jeu->compteur_impot++;
        if (jeu->compteur_impot == 15){
            jeu->compteur_impot = 0;
            impot(jeu);
        }
        for (int i = 0; i < jeu->nb_maisons; i++) {
            jeu->maisons[i].compteur_evolution++;
            if (jeu->maisons[i].compteur_evolution == 15) {
                jeu->maisons[i].compteur_evolution = 0;
                evolution_et_regression(jeu, i);
                maj_totale(jeu);
            }
        }
    }
}
