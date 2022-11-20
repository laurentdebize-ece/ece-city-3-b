#include "affichage.h"
#include <stdio.h>
#include <raylib.h>
#include "compteur.h"
#include <stdlib.h>
#include <time.h>


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
                    printf("%c ",jeu->map[colonne][ligne].symbole);
                }
                printf("\n");
            }
            break;
        case -1:
            for (ligne = 0; ligne < TAILLE_MAP_Y; ligne++) {
                for (colonne = 0; colonne < TAILLE_MAP_X; colonne++) {
                    if (jeu->map[colonne][ligne].symbole == SYMBOLE_ROUTE || jeu->map[colonne][ligne].symbole == SYMBOLE_CHATEAU_EAU) {
                        printf("%c ", jeu->map[colonne][ligne].symbole);
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
                    if (jeu->map[colonne][ligne].symbole == SYMBOLE_ROUTE || jeu->map[colonne][ligne].symbole == SYMBOLE_CENTRALE) {
                        printf("%c ", jeu->map[colonne][ligne].symbole);
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
/*
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
*/

void affichageMapRaylib(){
    InitWindow(LARGEUR_ECRAN, HAUTEUR_ECRAN, "Raylib test");

    srand(time(NULL)) ;

    //mise en place de la camera en 3D
    Camera3D camera = {0};
    camera.position = (Vector3){ 60, 60, 60 };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // ou pointe la camera
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // hauteur de la camera
    camera.fovy = 45.0f;                                // Champ de vision de la camera
    camera.projection = CAMERA_PERSPECTIVE;                   // Mode de la camera

    Ray ray = { 0 };        //on choisit le ray

    Vector3 positionCubeSol = {0.0f, 0.0f, 0.0f};
    Vector3 positionContourCarte = {0.5f, 0.0f, 0.5f};
    Vector3 positionHerbe1[1000];
    Vector3 positionHerbe2[1000];
    Vector3 positionHerbe3[1000];
    int nbMaison = 0;
    Manoires maison[100];


    // Quadrilatère sol
    Vector3 g0 = (Vector3){ -17.0f, 0.0f, -22.0f };
    Vector3 g1 = (Vector3){ -17.0f, 0.0f,  23.0f };
    Vector3 g2 = (Vector3){  18.0f, 0.0f,  23.0f };
    Vector3 g3 = (Vector3){  18.0f, 0.0f, -22.0f };

    for (int i = 0; i < 1000; i++){
        positionHerbe1[i].x = rand()%24;
        positionHerbe1[i].y = 0.0f;
        positionHerbe1[i].z = rand()%24;
        i = i + 1;
        positionHerbe1[i].x = -rand()%24;
        positionHerbe1[i].z = rand()%24;
        i = i + 1;
        positionHerbe1[i].x = rand()%24;
        positionHerbe1[i].z = -rand()%24;
        i = i + 1;
        positionHerbe1[i].x = -rand()%24;
        positionHerbe1[i].z = -rand()%24;
        i = i + 1;
    }

    for (int i = 0; i < 1000; i++){
        positionHerbe2[i].x = rand()%24;
        positionHerbe2[i].y = 0.0f;
        positionHerbe2[i].z = rand()%24;
        i = i + 1;
        positionHerbe2[i].x = -rand()%24;
        positionHerbe2[i].z = rand()%24;
        i = i + 1;
        positionHerbe2[i].x = rand()%24;
        positionHerbe2[i].z = -rand()%24;
        i = i + 1;
        positionHerbe2[i].x = -rand()%24;
        positionHerbe2[i].z = -rand()%24;
        i = i + 1;
    }

    for (int i = 0; i < 1000; i++){
        positionHerbe3[i].x = rand()%24;
        positionHerbe3[i].y = 0.0f;
        positionHerbe3[i].z = rand()%24;
        i = i + 1;
        positionHerbe3[i].x = -rand()%24;
        positionHerbe3[i].z = rand()%24;
        i = i + 1;
        positionHerbe3[i].x = rand()%24;
        positionHerbe3[i].z = -rand()%24;
        i = i + 1;
        positionHerbe3[i].x = -rand()%24;
        positionHerbe3[i].z = -rand()%24;
        i = i + 1;
    }
    Model sol = LoadModel("..\\3D\\ground_grass.obj");
    Model herbe1 = LoadModel("..\\3D\\grass.obj");
    Model herbe2 = LoadModel("..\\3D\\grass_large.obj");
    Model herbe3 = LoadModel("..\\3D\\grass_leafs.obj");
    Model maison1 = LoadModel("..\\3D\\house_type02.obj");
    Model cabane = LoadModel("..\\3D\\hangar_smallA.obj");
    Model immeuble = LoadModel("..\\3D\\large_buildingC.obj");
    Model gratteCiel = LoadModel("..\\3D\\skyscraperF.obj");
    Model chateauEau = LoadModel("..\\3D\\chateauEau.glb");
    Model usine = LoadModel("..\\3D\\victorian_factory.obj");
    Model route1 = LoadModel("..\\3D\\road_bendSidewalk.obj");
    Model route2 = LoadModel("..\\3D\\road_crossroad.obj");
    Model route3 = LoadModel("..\\3D\\road_end.obj");
    Model route4 = LoadModel("..\\3D\\road_intersectionPath.obj");

    SetCameraMode(camera, CAMERA_FREE);   // mode de camera libre
    SetExitKey(KEY_NULL);
    bool demandeDeFermetureWindow = false;   // booléen demandant à fermer la fenetre
    bool fermetureWindow = false;    // booléen permettant de quitter la fenetre
    SetTargetFPS(60);  // notre jeu tournera en 60 fps




    while (!fermetureWindow) {

        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)){
            demandeDeFermetureWindow = true;
        }
        if (demandeDeFermetureWindow == true){

            if (IsKeyPressed(KEY_Y)){
                fermetureWindow = true;
            }
            else if (IsKeyPressed(KEY_N)){
                demandeDeFermetureWindow = false;
            }
        }

        UpdateCamera(&camera);
        if (IsKeyDown('X')){
            camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        }
        // Permet de mettre en place le calcul des positions en 3D
        RayCollision collision = { 0 };
        collision.distance = FLT_MAX;
        collision.hit = false;

        // prend le ray et test en fonction du sol
        ray = GetMouseRay(GetMousePosition(), camera);

        // permet de checker la collision contre le sol
        RayCollision groundHitInfo = GetRayCollisionQuad(ray, g0, g1, g2, g3);

        if ((groundHitInfo.hit) && (groundHitInfo.distance < collision.distance))
        {
            collision = groundHitInfo;
        }


        BeginDrawing();





        ClearBackground(WHITE);

        BeginMode3D(camera);

        if (collision.hit)
        {

            Vector3 normalEnd;
            normalEnd.x = collision.point.x + collision.normal.x;
            normalEnd.y = collision.point.y + collision.normal.y;
            normalEnd.z = collision.point.z + collision.normal.z;

        }




        DrawGrid(50, 1);
        DrawModel(sol,positionCubeSol,TAILLE_PLATEAU,VERT_HERBE);
        DrawCubeWires(positionContourCarte, 35, 0, 45, BLACK);

        for(int i = 0; i < 1000; i++){
            DrawModel(herbe1, positionHerbe1[i], 1, WHITE);
            i = i + 1;
        }
        for(int i = 0; i < 1000; i++){
            DrawModel(herbe2, positionHerbe2[i], 1, GREEN);
            i = i + 1;
        }
        for(int i = 0; i < 1000; i++){
            DrawModel(herbe3, positionHerbe3[i], 1, LIME);
            i = i + 1;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            maison[nbMaison].pos_x = collision.point.x;
            maison[nbMaison].pos_y = collision.point.y;
            maison[nbMaison].pos_z = collision.point.z;
            nbMaison = nbMaison + 1;
        }

        for(int i = 0; i < nbMaison; i++){
            DrawModel(maison1, (Vector3){maison[i].pos_x,maison[i].pos_y,maison[i].pos_z},1,WHITE);
        }



        EndMode3D();


        if (collision.hit)
        {
            int ypos = 70;

            DrawText(TextFormat("Distance camera: %3.2f", collision.distance), 10, ypos, 10, BLACK);

            DrawText(TextFormat("Position souris sur plateau : x = %3.2f y = %3.2f z = %3.2f",
                                collision.point.x,
                                collision.point.y,
                                collision.point.z), 10, ypos + 15, 10, BLACK);

            DrawText(TextFormat("Norme: %3.2f %3.2f %3.2f",
                                collision.normal.x,
                                collision.normal.y,
                                collision.normal.z), 10, ypos + 30, 10, BLACK);

        }



        DrawFPS(10, 10);


        if (demandeDeFermetureWindow){
            DrawRectangle(0, 100, LARGEUR_ECRAN, 200, BLACK);
            DrawText("Voulez vous fermer la fenetre ? [Y/N]", 325, 180, 30, WHITE);
        }

        EndDrawing();
    }
    CloseWindow();
}