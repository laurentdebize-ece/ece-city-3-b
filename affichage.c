#include "affichage.h"
#include <stdio.h>
#include <raylib.h>


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
