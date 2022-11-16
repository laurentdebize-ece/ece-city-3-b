#include "affichage.h"
#include <stdio.h>
#include <raylib.h>
#include "compteur.h"


void afficherCarte(Case** map){
    printf("   ");
    for(int i = 0; i < TAILLE_MAP_X; i++){
        if(i < 10){
            printf(" ");
        }
        printf("%d ",i);
    }
    printf("\n");
    for(int i = 0; i < TAILLE_MAP_Y; i++){
        if(i < 10){
            printf(" ");
        }
        printf("%d ",i);
        for(int j = 0; j < TAILLE_MAP_X; j++){
            printf(" %c ", map[j][i].symbole);
        }
        printf("\n");
    }
}

//affichage de la map à partir du fichier texte lu
void afficherMap(Jeu * jeu, int niveau) {
    int ligne, colonne;
    switch (niveau) {
        case 0:
            printf("nbHabitations : %d\n", jeu->nb_maisons);
            for (ligne = 0; ligne < TAILLE_MAP_Y; ligne++) {
                for (colonne = 0; colonne < TAILLE_MAP_X; colonne++) {
                    printf("%c ",jeu->map[ligne][colonne].symbole);
                }
                printf("\n");
            }
            break;
        case -1:
            for (ligne = 0; ligne < TAILLE_MAP_Y; ligne++) {
                for (colonne = 0; colonne < TAILLE_MAP_X; colonne++) {
                    if (jeu->map[ligne][colonne].symbole == SYMBOLE_ROUTE || jeu->map[ligne][colonne].symbole == SYMBOLE_CHATEAU_EAU) {
                        printf("%c ", jeu->map[ligne][colonne].symbole);
                    } else {
                        printf("0 ");
                    }
                }
                printf("\n");
            }
            break;
        case -2:
            for (ligne = 0; ligne < TAILLE_MAP_Y; ligne++) {
                for (colonne = 0; colonne < TAILLE_MAP_X; colonne++) {
                    if (jeu->map[ligne][colonne].symbole == SYMBOLE_ROUTE || jeu->map[ligne][colonne].symbole == SYMBOLE_CENTRALE) {
                        printf("%c ", jeu->map[ligne][colonne].symbole);
                    } else {
                        printf("0 ");
                    }
                }
                printf("\n");
            }
            break;
        default:
            printf("erreur niveau\n");
            break;
    }
    afficherCompteur(*jeu);
}

void afficherCarteRaylib(){
    // initialisation
    const int screenWidth = 2000;
    const int screenHeight = 1450;

    InitWindow(screenWidth, screenHeight, "carte");

    // camera en 3D
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FREE); // mode de la camera

    SetTargetFPS(60);                   // fps
    while (!WindowShouldClose()){
        // mise a jour
        UpdateCamera(&camera);

        // dessiner
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        DrawGrid(46, 2);


        EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}
