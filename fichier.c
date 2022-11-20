#include "fichier.h"

// fonction pour charger la map à partir d'un fichier texte (nouveau ou sauvegardé au préalalble)
Case **chargerMap(Jeu *jeu) {
    FILE *fichier = fopen("../map.txt", "r");
    char caractereLu;
    //Initialisation des variables
    int ligne = 0, colonne = 0;
    char myCaractere;
    Case **map = malloc(sizeof(Case *) * TAILLE_MAP_X);

    for (int i = 0; i < TAILLE_MAP_X; i++) {
        map[i] = malloc(sizeof(Case) * TAILLE_MAP_Y);
    }
    // on charge le niveau 0 à partir d'un fichier txt
    if (fichier != NULL) {
        //fscanf(fichier, "%d", &jeu->argent);
        //fscanf(fichier, "%d", &jeu->nb_maisons);
        //do {
            for (ligne = 0; ligne < TAILLE_MAP_Y; ligne++) {
                for (colonne = 0; colonne < TAILLE_MAP_X ; colonne++) {
                    caractereLu = fgetc(fichier);
                    myCaractere = caractereLu;
                    map[colonne][ligne].occupe = false;
                    map[colonne][ligne].symbole = myCaractere;
               }
                caractereLu = fgetc(fichier);//pour lite le \n
            }
        //} while (caractereLu != EOF); // On continue tant le caractere lu n'est pas EndOfFile (fin de fichier)
        fclose(fichier); // On ferme le fichier
    } else {
        printf("fichier vide\n");
    }
    return map;
}

//fonction pour sauvegarder la map à la fin de la partie
void sauvegarderJeu(Jeu * jeu) {
    //lecture des fichiers
    FILE *fichierMap = fopen("../map.txt", "w");
    FILE *fichierJeu = fopen("../caracteristiques.txt", "w");
    int ligne = 0, colonne = 0;
    char caractere;
    // on sauvegarde le niveau 0 à partir des tableaux qui ont été modifiés au cours de la partie
    if (fichierMap != NULL) {
        for (ligne = 0; ligne < TAILLE_MAP_Y; ligne++) {
            for (colonne = 0; colonne < TAILLE_MAP_X; colonne++) {
                caractere= jeu->map[colonne][ligne].symbole;
                //fprintf(fichierMap, "%c", jeu->map[ligne][colonne].symbole);
                fputc(caractere, fichierMap);
            }
            //fprintf(fichierMap, "\n");
            fputc('\n', fichierMap);
        }
        fclose(fichierMap); // On ferme le fichier
    } else {
        printf("fichier vide\n");
    }
    // création d'un fichier de sauvegarde des elements du jeu autre que la map (argent joueur/ nbMaisons/ nbcentrales/etc...)
    fprintf(fichierJeu, "%d\n", jeu->argent);
    fprintf(fichierJeu, "%d\n", jeu->nb_maisons);
    fprintf(fichierJeu, "%d\n", jeu->nb_routes);
    fprintf(fichierJeu, "%d\n", jeu->nb_centrales);
    fprintf(fichierJeu, "%d\n", jeu->nb_chateau_eau);

    // stockage des caracteristiques de chaque maison
    for(int i = 0; i < jeu->nb_routes; i++){
        fprintf(fichierJeu, "%d ", jeu->routes[i].pos_x);
        fprintf(fichierJeu, "%d\n", jeu->routes[i].pos_y);
    }
    for(int i = 0; i < jeu->nb_maisons; i++){
        fprintf(fichierJeu, "%d ", jeu->maisons[i].pos_x);
        fprintf(fichierJeu, "%d ", jeu->maisons[i].pos_y);
        fprintf(fichierJeu, "%d ", jeu->maisons[i].niveau);
        fprintf(fichierJeu, "%d ", jeu->maisons[i].habitants);
        fprintf(fichierJeu, "%d ", jeu->maisons[i].eau);
        fprintf(fichierJeu, "%d\n", jeu->maisons[i].electricite);
    }
    for(int i = 0; i < jeu->nb_centrales+jeu->nb_chateau_eau; i++){
        fprintf(fichierJeu, "%d ", jeu->batiments[i].pos_x);
        fprintf(fichierJeu, "%d ", jeu->batiments[i].pos_y);
        fprintf(fichierJeu, "%d ", jeu->batiments[i].type_batiment);
        fprintf(fichierJeu, "%d ", jeu->batiments[i].capacite);
        fprintf(fichierJeu, "%d\n", jeu->batiments[i].horizontal);
    }
    fclose(fichierJeu); // On ferme le fichier
}

// fonction pour changer de niveau
void changerNiv(int *nivAct, Jeu * jeu) {
    int choix = 0;
    if (*nivAct == 0) {
        printf("quel niveau voulez vous visualiser ?\n -1 : réseau de canalisation \n -2 : réseau electrique\n");
        scanf("%d", &choix);
        switch (choix) {
            case -1 :
                *nivAct = choix;
                printf("niveauActuel : %d\n", *nivAct);
                afficherMap(jeu, *nivAct);
                break;
            case -2 :
                *nivAct = choix;
                printf("niveauActuel : %d\n", *nivAct);
                afficherMap(jeu, *nivAct);
                break;
            default:
                break;
        }
    } else if (*nivAct == -1) {
        printf("quel niveau voulez vous visualiser ?\n  0 : map \n -2 : réseau electrique\n");
        scanf("%d", &choix);
        switch (choix) {
            case 0 :
                *nivAct = choix;
                printf("niveauActuel : %d\n", *nivAct);
                afficherMap(jeu, *nivAct);
                break;
            case -2 :
                *nivAct = choix;
                printf("niveauActuel : %d\n", *nivAct);
                afficherMap(jeu, *nivAct);
                break;
            default:
                break;
        }
    } else {
        printf("quel niveau voulez vous visualiser ?\n  0 : map \n -1 : réseau de canalisation \n");
        scanf("%d", &choix);
        switch (choix) {
            case -1 :
                *nivAct = choix;
                printf("niveauActuel : %d\n", *nivAct);
                afficherMap(jeu, *nivAct);
                break;
            case 0 :
                *nivAct = choix;
                printf("niveauActuel : %d\n", *nivAct);
                afficherMap(jeu, *nivAct);
                break;
            default:
                break;
        }
    }
}

// fonctions pour permettre au joueur de choisir le type et l'emplacement de sa construction
char choixConstruction(char *type) {
    char type_de_construction;
    switch (*type) {
        case 'R':
            type_de_construction = TYPE_ROUTE;
            break;
        case 'H':
            type_de_construction = TYPE_MAISON;
            break;
        case 'C':
            type_de_construction = TYPE_CENTRALE;
            break;
        case 'E':
            type_de_construction = TYPE_CHATEAU_EAU;
            break;
        default:
            printf("erreur choix construction\n");
            break;
    }
    return type_de_construction;
}

bool  choixEmplacement(int *ligne, int *colonne, Jeu*  jeu) {
    scanf("%d/%d", ligne, colonne);
    if (jeu->map[*colonne][*ligne].occupe == true){
        return false;
    }
    else {
        return true;
    }
}

