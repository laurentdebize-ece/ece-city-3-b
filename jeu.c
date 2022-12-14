//
// Created by Mona Lias on 11/13/22.
//

#include "jeu.h"
#include "compteur.h"
#include "eau.h"
#include "elec.h"

void timer(Jeu * jeu){
    time_t time_null = time(NULL);
    if (jeu->temps!=time_null){
        jeu->temps = time_null;
        for (int i = 0; i < jeu->nb_maisons; i++) {
            jeu->maisons[i].timer++;
            if (jeu->maisons[i].timer % 15 == 0){
                evolution_et_regression(jeu, i);
                compteur_cycle_maison(jeu);
            }
        }

    }
}

Jeu reprendrePartie() {
    FILE *fichierJeu = fopen("../caracteristiques.txt", "r");
    Jeu jeu;
    int argentPred, eau, elec, nbRoute, nbMaison, nbCentrale, nbChateau;
    jeu = initialisation_jeu();
    fscanf(fichierJeu, "%d", &argentPred);
    fscanf(fichierJeu, "%d", &nbMaison);
    fscanf(fichierJeu, "%d", &nbRoute);
    fscanf(fichierJeu, "%d", &nbCentrale);
    fscanf(fichierJeu, "%d", &nbChateau);

    // detecter les routes
    for (int i = 0; i < nbRoute; i++) {
        fscanf(fichierJeu, "%d", &jeu.routes[i].pos_x);
        fscanf(fichierJeu, "%d", &jeu.routes[i].pos_y);
        construire(&jeu, TYPE_ROUTE, jeu.routes[i].pos_x, jeu.routes[i].pos_y, 0);
        fscanf(fichierJeu, "\n");
    }
    // detecter les maisons + routes adjacentes
    for (int i = 0; i < nbMaison; i++) {
        fscanf(fichierJeu, "%d", &jeu.maisons[i].pos_x);
        fscanf(fichierJeu, "%d", &jeu.maisons[i].pos_y);
        fscanf(fichierJeu, "%d", &jeu.maisons[i].niveau);
        fscanf(fichierJeu, "%d", &jeu.maisons[i].habitants);
        fscanf(fichierJeu, "%d", &jeu.maisons[i].eau);
        fscanf(fichierJeu, "%d", &jeu.maisons[i].electricite);
        construire(&jeu, TYPE_MAISON, jeu.maisons[i].pos_x, jeu.maisons[i].pos_y, 0);
        fscanf(fichierJeu, "\n");
    }
    // detecter les centrales et leur routes adjacentes
    for (int i = 0; i < nbCentrale + nbChateau; i++) {
        fscanf(fichierJeu, "%d", &jeu.batiments[i].pos_x);
        fscanf(fichierJeu, "%d", &jeu.batiments[i].pos_y);
        fscanf(fichierJeu, "%d", &jeu.batiments[i].type_batiment);
        fscanf(fichierJeu, "%d", &jeu.batiments[i].capacite);
        int horizontal;
        fscanf(fichierJeu, "%d", &horizontal);
        // pour faire fonctionner le bouleen est reussir a lire le fichier quand meme car on print dans le fichier un int 0/1
        if (horizontal == 1) {
            jeu.batiments[i].horizontal = true;
        } else {
            jeu.batiments[i].horizontal = false;
        }
        construire(&jeu, jeu.batiments[i].type_batiment, jeu.batiments[i].pos_x, jeu.batiments[i].pos_y,
                   jeu.batiments[i].horizontal);
        fscanf(fichierJeu, "\n");
    }
    jeu.argent = argentPred;
    return jeu;
}

bool jouer(Jeu *jeu, int *niveauActuel) {
    bool choixOk = false;
    bool end = false;
    bool isCaseLibre = false;
    int choix= -1;
    int ligne, colonne, sauvegarde,type;
    char choixType;
    FILE *fichierJeu = fopen("../caracteristiques.txt", "r");

    // test pour savoir si on commence une nouvelle partie ou si on reprend une partie sauvegardee
    if (fichierJeu != NULL) {
        *jeu = reprendrePartie();
    } else {
        *jeu = initialisation_jeu();
        choix_mode_jeu(jeu);
    }
    compteur_debut_cycle(jeu);
    //charger la map ?? partir du fichier
    jeu->map = chargerMap(jeu);
    printf("niveauActuel : %d\n", *niveauActuel);
    afficherMap(jeu, *niveauActuel);
    while (end != true) {
        // mettre a jour les compteurs a chaque cycles
        compteur_debut_cycle(jeu);
        timer(jeu);
        while (choixOk != true ) {
            printf("Que voulez vous faire ?\n 1- changer de niveau de visualisation\n 2- construire\n 3- detruire\n 0- Quitter le jeu\n");
            scanf("%d", &choix);
            if (choix ==0 || choix == 1 || choix == 2 || choix == 3){
                choixOk= true;
            }
        }
        choixOk=false;
        switch (choix) {
            case 0:
                printf("Voulez vous sauvegarder la partie ? (1=oui/0=non) \n");
                fflush(stdin);
                scanf("%d", &sauvegarde);
                if (sauvegarde == 1) {
                    sauvegarderJeu(jeu);
                }
                end = true;
                break;
            case 1:
                changerNiv(niveauActuel, jeu);
                break;
            case 2:
                while (choixOk != true) {
                    printf("que souhaitez vous construire ?\n R- Route\n H- Habitation\n C- Centrale\n E- Chateau\n");
                    fflush(stdin);
                    scanf("%c", &choixType);
                    if (choixType == 'R' || choixType == 'H' || choixType == 'C' || choixType == 'E') {
                        choixOk = true;
                    }
                }
                type = choixConstruction(&choixType);
                while (isCaseLibre == false) {
                    printf("ou voulez vous construire (ligne/colonne) ?\n");
                    fflush(stdin);
                    isCaseLibre = choixEmplacement(&ligne, &colonne, jeu);
                }
                isCaseLibre = false;
                construire(jeu, type, colonne, ligne, 0);
                afficherMap(jeu, *niveauActuel);
                choixOk = false;
                break;
            case 3:
                while (choixOk != true) {
                    printf("que souhaitez vous detruire ?\n R- Route\n H- Habitation\n C- Centrale\n E- Chateau\n");
                    fflush(stdin);
                    scanf("%c", &choixType);
                    if (choixType == 'R' || choixType == 'H' || choixType == 'C' || choixType == 'E') {
                        choixOk = true;
                    }
                }
                type = choixConstruction(&choixType);
                printf("ou voulez vous detruire (ligne/colonne) ?\n");
                choixEmplacement(&ligne, &colonne, jeu);
                if (type == TYPE_ROUTE) {
                    detruire(jeu, colonne, ligne);
                } else {
                    int numero;
                    trouverNumero_et_TypeBatiment(jeu, &type, &numero, colonne, ligne);
                    detruire(jeu, 0, 0);
                }
                afficherMap(jeu, *niveauActuel);
                choixOk = false;
                break;
            default :
                printf("erreur num??ro veuillez r??essayer\n");
                break;
        }
        if (jeu->nb_chateau_eau !=0 || jeu->nb_centrales !=0 ) {
            repartitionEau(jeu);
            repartition_electricite(jeu);
            repartition_habitants(jeu);
        }
        printf("eau maison : %d\n", jeu->maisons[0].eau);
        printf("electricite maison : %d\n", jeu->maisons[0].electricite);
    }
    return true;
}

