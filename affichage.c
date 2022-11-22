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

void initCases(Case cases[LARGEUR_PLATEAU][LONGUEUR_PLATEAU]){
    int i,j;
    for(i = 0; i < LARGEUR_PLATEAU;i++){
        for(j = 0; j < LONGUEUR_PLATEAU;j++){
            cases[i][j].largeur = 1;
            cases[i][j].hauteur = 1;
            cases[i][j].x = 18 - 0.5 - i;
            cases[i][j].z = -22 + 0.5 + j;
            cases[i][j].occupe = false;

        }
    }
}

void dessinerCases(Case cases[LARGEUR_PLATEAU][LONGUEUR_PLATEAU]){
    int i, j;
    for(i = 0; i < LARGEUR_PLATEAU; i++){
        for(j = 0; j < LONGUEUR_PLATEAU; j++){
            DrawCubeWires((Vector3){cases[i][j].x,0.0f,cases[i][j].z}, cases[i][j].largeur, 0, cases[i][j].hauteur, RAYWHITE);
        }
    }
}

void affichageMapRaylib(){
    InitWindow(LARGEUR_ECRAN, HAUTEUR_ECRAN, "Raylib test");

    srand(time(NULL)) ;

    //mise en place de la camera en 3D
    Camera3D camera = {0};
    camera.position = (Vector3){ 40, 40, 40 };
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
    int nbUsine = 0;
    int nbChateauEau = 0;
    int nbroute = 0;
    Manoires maison[100];
    Usines usines[100];
    ChateauEau chateauDo[100];
    Routes routes[100];
    Case cases[LARGEUR_PLATEAU][LONGUEUR_PLATEAU];
    initCases(cases);


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
    Model usine = LoadModel("..\\3D\\usine.glb");
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





        DrawModel(sol,positionCubeSol,TAILLE_PLATEAU,VERT_HERBE);
        dessinerCases(cases);
        DrawCubeWires(positionContourCarte, LARGEUR_PLATEAU, 0, LONGUEUR_PLATEAU, BLACK);
        DrawGrid(50, 1);

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
            int i,j;
            for(i = 0; i < LARGEUR_PLATEAU;i++){
                for(j = 0; j < LONGUEUR_PLATEAU;j++){
                    if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 && collision.point.x  <= cases[i][j].x + 0.5  && collision.point.x >= cases[i][j].x - 0.5){
                        maison[nbMaison].pos_x = cases[i][j].x + 1;
                        maison[nbMaison].pos_y = collision.point.y;
                        maison[nbMaison].pos_z = cases[i][j].z - 1;
                        nbMaison = nbMaison + 1;
                    }

                }
            }
        }

        if (IsKeyPressed(KEY_U)){
            int i,j;
            for(i = 0; i < LARGEUR_PLATEAU;i++){
                for(j = 0; j < LONGUEUR_PLATEAU;j++){
                    if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 && collision.point.x  <= cases[i][j].x + 0.5  && collision.point.x >= cases[i][j].x - 0.5){
                        usines[nbUsine].pos_x = cases[i][j].x + 2.5;
                        usines[nbUsine].pos_y = collision.point.y;
                        usines[nbUsine].pos_z = cases[i][j].z - 1.5;
                        nbUsine = nbUsine + 1;
                    }

                }
            }
        }
        if (IsKeyPressed(KEY_C)){
            int i,j;
            for(i = 0; i < LARGEUR_PLATEAU;i++){
                for(j = 0; j < LONGUEUR_PLATEAU;j++){
                    if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 && collision.point.x  <= cases[i][j].x + 0.5  && collision.point.x >= cases[i][j].x - 0.5){
                        chateauDo[nbChateauEau].pos_x = cases[i][j].x;
                        chateauDo[nbChateauEau].pos_y = collision.point.y;
                        chateauDo[nbChateauEau].pos_z = cases[i][j].z;
                        nbChateauEau = nbChateauEau + 1;
                    }

                }
            }
        }
        if (IsKeyPressed(KEY_R)){
            int i,j;
            for(i = 0; i < LARGEUR_PLATEAU;i++){
                for(j = 0; j < LONGUEUR_PLATEAU;j++){
                    if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 && collision.point.x  <= cases[i][j].x + 0.5  && collision.point.x >= cases[i][j].x - 0.5){
                        routes[nbroute].pos_x = cases[i][j].x;
                        routes[nbroute].pos_y = collision.point.y;
                        routes[nbroute].pos_z = cases[i][j].z;
                        nbroute = nbroute + 1;
                    }

                }
            }
        }

        for(int i = 0; i < nbMaison; i++){
            DrawModel(maison1, (Vector3){maison[i].pos_x,maison[i].pos_y,maison[i].pos_z},2,WHITE);
        }
        for(int i = 0; i < nbUsine; i++){
            DrawModel(usine, (Vector3){usines[i].pos_x,usines[i].pos_y,usines[i].pos_z},0.003,WHITE);
        }
        for(int i = 0; i < nbChateauEau; i++){
            DrawModel(chateauEau, (Vector3){chateauDo[i].pos_x,chateauDo[i].pos_y,chateauDo[i].pos_z},0.002,WHITE); // modele chateau eau ne marche pas
        }
        for(int i = 0; i < nbroute; i++){
            DrawModel(route1, (Vector3){routes[i].pos_x,routes[i].pos_y,routes[i].pos_z},1,WHITE);
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