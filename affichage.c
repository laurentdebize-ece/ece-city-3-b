#include "affichage.h"
#include <stdio.h>
#include <raylib.h>
#include "compteur.h"
#include <stdlib.h>
#include <time.h>
#include "construction_destruction.h"

#define screenWidth 2000
#define screenHeight 1450



void choixM(Jeu jeu){
    bool exit = true;
    float scrollingBack = 0.0f;


    Image choix = LoadImage("../image/choix.png");
    Image capitaliste = LoadImage("../image/capitaliste.png");
    Image communiste = LoadImage("../image/communiste.png");
    Image simcityflou = LoadImage("../image/simcity.png");


    Texture2D Choix = LoadTextureFromImage(choix);
    Texture2D Capitaliste = LoadTextureFromImage(capitaliste);
    Texture2D Communiste = LoadTextureFromImage(communiste);
    Texture2D Simcityflou = LoadTextureFromImage(simcityflou);


    UnloadImage(choix);
    UnloadImage(capitaliste);
    UnloadImage(communiste);
    UnloadImage(simcityflou);

    while (!WindowShouldClose()){

        scrollingBack -= 0.1f;
        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -Simcityflou.width * 10) scrollingBack = 0;


        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureEx(Simcityflou, (Vector2){scrollingBack, 20 }, 0.0f, 1.7f, WHITE);
        DrawTextureEx(Simcityflou, (Vector2){Simcityflou.width * 2 , 20 }, 0.0f, 1.7f, WHITE);


        DrawTextureEx(Choix, (Vector2){35,200 }, 0.0f, 1.0f, WHITE);
        if((GetMousePosition().x >= 270) && (GetMousePosition().x <=  750) && (GetMousePosition().y >= 670) && (GetMousePosition().y <= 810)){
            DrawTextureEx(Capitaliste, (Vector2){35,200 }, 0.0f, 1.0f, WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                jeu.mode_jeu = 1;
            }
        }
        if((GetMousePosition().x >= 1200) && (GetMousePosition().x <=  1700) && (GetMousePosition().y >= 670) && (GetMousePosition().y <= 810)){
            DrawTextureEx(Communiste, (Vector2){35,200 }, 0.0f, 1.0f, WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                jeu.mode_jeu = 2;
            }
        }


        EndDrawing();
    }
    UnloadTexture(Choix);
    UnloadTexture(Capitaliste);
    UnloadTexture(Communiste);
    CloseWindow();
}


void menu1(){
    // Pour longueur et largeur: screenWidth 2000, screenHeight 1450
    float scrollingBack = 0.0f;
    bool exit = false;
    Jeu jeu;

    InitWindow(screenWidth, screenHeight, "menu");
    Image simcity = LoadImage("../image/simcity.png");
    Image logo = LoadImage("../image/logoSimcity.png");
    Image bouton = LoadImage("../image/logo.png");
    Image bouton2 = LoadImage("../image/logoclick.png");

    Texture2D Simcity = LoadTextureFromImage(simcity);
    Texture2D Logo = LoadTextureFromImage(logo);
    Texture2D Bouton = LoadTextureFromImage(bouton);
    Texture2D Bouton2 = LoadTextureFromImage(bouton2);


    UnloadImage(simcity);
    UnloadImage(logo);
    UnloadImage(bouton);
    UnloadImage(bouton2);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        scrollingBack -= 0.1f;
        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -simcity.width * 10) scrollingBack = 0;

        BeginDrawing();
        ClearBackground(WHITE);

        // DrawTexture(Simcity,0,0,WHITE);
        DrawTextureEx(Simcity, (Vector2){scrollingBack, 20 }, 0.0f, 1.7f, WHITE);
        DrawTextureEx(Simcity, (Vector2){simcity.width * 2 , 20 }, 0.0f, 1.7f, WHITE);

        DrawTextureEx(Logo, (Vector2){150,100 }, 0.0f, 1.8f, WHITE);
        DrawTextureEx(Bouton, (Vector2){585,500 }, 0.0f, 0.5f, WHITE);
        if((GetMousePosition().x >= 870) && (GetMousePosition().x <= 1250) && (GetMousePosition().y >= 720) && (GetMousePosition().y <= 820)){
            DrawTextureEx(Bouton2, (Vector2){585,500 }, 0.0f, 0.5f, WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                choixM(jeu);
            }
        }

        //DrawText("jouer", 940, 710, 100, RED);
        //si bouton dans la zone du bouton jouer d'une autre couleur

        EndDrawing();
    }

    UnloadTexture(Simcity);
    UnloadTexture(Logo);
    UnloadTexture(Bouton);
    CloseWindow();
}


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
    compteur_cycle_maison(jeu);
    afficherCompteur(*jeu);
    if (jeu->mode_jeu == 1) {
        printf("mode jeu : Capitaliste\n");
    }else{
        printf("mode jeu : Communiste\n");
    }
}

void initCases(Case cases[TAILLE_MAP_X][TAILLE_MAP_Y]){
    int i,j;
    for(i = 0; i < TAILLE_MAP_X;i++){
        for(j = 0; j < TAILLE_MAP_Y;j++){
            cases[i][j].largeur = 1;
            cases[i][j].hauteur = 1;
            cases[i][j].z = 23 - 0.5 - i;
            cases[i][j].x = -17 + 0.5 + j;
            cases[i][j].occupe = false;

        }
    }
}

void dessinerCases(Case cases[TAILLE_MAP_X][TAILLE_MAP_Y]){
    int i, j;
    for(i = 0; i < TAILLE_MAP_X; i++){
        for(j = 0; j < TAILLE_MAP_Y; j++){
            DrawCubeWires((Vector3){cases[i][j].x,0.0f,cases[i][j].z}, cases[i][j].largeur, 0, cases[i][j].hauteur, RAYWHITE);
        }
    }
}

void affichageMapRaylib(Jeu* jeu){
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
    Case cases[TAILLE_MAP_X][TAILLE_MAP_Y];
    initCases(cases);


    // Quadrilatère sol
    Vector3 g0 = (Vector3){ -50.0f, 0.0f, -50.0f };
    Vector3 g1 = (Vector3){ -50.0f, 0.0f,  50.0f };
    Vector3 g2 = (Vector3){  50.0f, 0.0f,  50.0f };
    Vector3 g3 = (Vector3){  50.0f, 0.0f, -50.0f };
    Vector3 axeRotation = (Vector3){0.0f,1.0f,0.0f};

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
    Model route5 = LoadModel("..\\3D\\road_straight.obj");


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





        ClearBackground(SKYBLUE);

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
        DrawCubeWires(positionContourCarte, TAILLE_MAP_Y, 0, TAILLE_MAP_X, BLACK);
       // DrawGrid(50, 1);

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
            for(i = 0; i < TAILLE_MAP_X;i++){
                for(j = 0; j < TAILLE_MAP_Y;j++){
                    if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 && collision.point.x  <= cases[i][j].x + 0.5  && collision.point.x >= cases[i][j].x - 0.5){
                        if (construire(jeu, TYPE_MAISON,i,j,0)) {
                            jeu->maisons[jeu->nb_maisons - 1].position.pos_x= cases[i][j].x + 1;
                            jeu->maisons[jeu->nb_maisons - 1].position.pos_y= collision.point.y;
                            jeu->maisons[jeu->nb_maisons - 1].position.pos_z= cases[i][j].z - 1;
                            jeu->maisons[jeu->nb_maisons - 1].niveau= NIVEAU_CABANE;
                        }
                    }

                }
            }
        }

        if (IsKeyPressed(KEY_U)){
            int i,j;
            for(i = 0; i < TAILLE_MAP_X;i++){
                for(j = 0; j < TAILLE_MAP_Y;j++){
                    if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 && collision.point.x  <= cases[i][j].x + 0.5  && collision.point.x >= cases[i][j].x - 0.5){
                        if (construire(jeu, TYPE_CENTRALE,i,j,0)) {
                            jeu->batiments[jeu->nb_centrales + jeu->nb_chateau_eau - 1].position.pos_x= cases[i][j].x + 2.5;
                            jeu->batiments[jeu->nb_centrales + jeu->nb_chateau_eau - 1].position.pos_y= collision.point.y;
                            jeu->batiments[jeu->nb_centrales + jeu->nb_chateau_eau - 1].position.pos_z= cases[i][j].z - 1.5;
                        }
                    }


                }
            }
        }
        if (IsKeyPressed(KEY_C)){
            int i,j;
            for(i = 0; i < TAILLE_MAP_X;i++){
                for(j = 0; j < TAILLE_MAP_Y;j++){
                    if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 && collision.point.x  <= cases[i][j].x + 0.5  && collision.point.x >= cases[i][j].x - 0.5){
                        if (construire(jeu, TYPE_CHATEAU_EAU,i,j,0)) {
                            jeu->batiments[jeu->nb_centrales + jeu->nb_chateau_eau - 1].position.pos_x= cases[i][j].x;
                            jeu->batiments[jeu->nb_centrales + jeu->nb_chateau_eau - 1].position.pos_y= collision.point.y;
                            jeu->batiments[jeu->nb_centrales + jeu->nb_chateau_eau - 1].position.pos_z= cases[i][j].z;
                        }
                    }

                }
            }
        }
        if (IsKeyPressed(KEY_R)){
            int i,j;
            for(i = 0; i < TAILLE_MAP_X;i++){
                for(j = 0; j < TAILLE_MAP_Y;j++){
                    if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 && collision.point.x  <= cases[i][j].x + 0.5  && collision.point.x >= cases[i][j].x - 0.5){
                        if (construire(jeu, TYPE_ROUTE,i,j,0)) {
                            jeu->routes[jeu->nb_routes - 1].position.pos_x= cases[i][j].x;
                            jeu->routes[jeu->nb_routes - 1].position.pos_y= collision.point.y;
                            jeu->routes[jeu->nb_routes - 1].position.pos_z= cases[i][j].z;
                        }
                    }

                }
            }
        }

        if(IsKeyPressed(KEY_D)){
            int i,j;
            for(i = 0; i < TAILLE_MAP_X;i++) {
                for (j = 0; j < TAILLE_MAP_Y; j++) {
                    if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 &&
                        collision.point.x <= cases[i][j].x + 0.5 && collision.point.x >= cases[i][j].x - 0.5) {
                        detruire(jeu,i,j);

                    }
                }
            }
        }

        for(int i = 0; i < jeu->nb_maisons; i++){
            switch(jeu->maisons[i].niveau){
                case NIVEAU_TERRAIN_VAGUE:
                    DrawModel(maison1, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,WHITE);
                    break;
                case NIVEAU_RUINE:
                    DrawModel(maison1, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,WHITE);
                    break;
                case NIVEAU_CABANE:
                    DrawModel(cabane, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},1,WHITE);
                    break;
                case NIVEAU_MAISON:
                    DrawModel(maison1, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,WHITE);
                    break;
                case NIVEAU_IMMEUBLE:
                    DrawModel(immeuble, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2.7,WHITE);
                    break;
                case NIVEAU_GRATTE_CIEL:
                    DrawModel(gratteCiel, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,WHITE);
                    break;
            }
        }


        for(int i = 0; i < jeu->nb_centrales+jeu->nb_chateau_eau; i++){
            switch (jeu->batiments[i].type_batiment) {
                case TYPE_CHATEAU_EAU:
                    DrawModel(chateauEau, (Vector3){jeu->batiments[i].position.pos_x,jeu->batiments[i].position.pos_y,jeu->batiments[i].position.pos_z},0.002,WHITE);
                    break;
                case TYPE_CENTRALE:
                    DrawModel(usine, (Vector3){jeu->batiments[i].position.pos_x,jeu->batiments[i].position.pos_y,jeu->batiments[i].position.pos_z},0.003,WHITE);
                    break;
            }
        }

        for(int i = 0; i < jeu->nb_routes; i++){
            bool routes_a_cote[4] = {false};
            Liste* tmp = jeu->routes[i].adjacente_route;
            while(tmp != NULL){
                if(jeu->routes[tmp->numero].pos_x < jeu->routes[i].pos_x){
                    routes_a_cote[ROUTE_OUEST] = true;
                }
                else if (jeu->routes[tmp->numero].pos_x > jeu->routes[i].pos_x){
                    routes_a_cote[ROUTE_EST] = true;
                }
                else if(jeu->routes[tmp->numero].pos_y < jeu->routes[i].pos_y){
                    routes_a_cote[ROUTE_NORD] = true;
                }
                else{
                    routes_a_cote[ROUTE_SUD] = true;
                }
                tmp = tmp->suivant;
            }
            if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_EST] && routes_a_cote[ROUTE_OUEST]){
                DrawModel(route2, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z},1,WHITE);

            }
            else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_EST]){
                DrawModelEx(route4, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 180.0f, (Vector3){1,1,1}, WHITE);
            }
            else if(routes_a_cote[ROUTE_OUEST] && routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_EST]){
                DrawModelEx(route4, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, -90.0f, (Vector3){1,1,1}, WHITE);
            }
            else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_OUEST] && routes_a_cote[ROUTE_EST]){
                DrawModelEx(route4, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 90.0f, (Vector3){1,1,1}, WHITE);
            }
            else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_OUEST]){
                DrawModel(route4, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z},1,WHITE);
            }
            else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_NORD]){
                DrawModel(route5, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z},1,WHITE);
            }
            else if(routes_a_cote[ROUTE_EST] && routes_a_cote[ROUTE_OUEST]){
                DrawModelEx(route5, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 90.0f, (Vector3){1,1,1}, WHITE);
            }
            else if(routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_OUEST]){
                DrawModelEx(route1, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 0.0f, (Vector3){1,1,1}, WHITE);
            }
            else if(routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_EST]){
                DrawModelEx(route1, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, -90.0f, (Vector3){1,1,1}, WHITE);
            }
            else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_OUEST]){
                DrawModelEx(route1, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 90.0f, (Vector3){1,1,1}, WHITE);
            }
            else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_EST]){
                DrawModelEx(route1, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, -180.0f, (Vector3){1,1,1}, WHITE);
            }
            else if(routes_a_cote[ROUTE_SUD]){
                DrawModelEx(route3, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 0.0f, (Vector3){1,1,1}, WHITE);
            }
            else if(routes_a_cote[ROUTE_NORD]){
                DrawModelEx(route3, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 180.0f, (Vector3){1,1,1}, WHITE);
            }
            else if(routes_a_cote[ROUTE_OUEST]){
                DrawModelEx(route3, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, -90.0f, (Vector3){1,1,1}, WHITE);
            }
            else if(routes_a_cote[ROUTE_EST]){
                DrawModelEx(route3, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 90.0f, (Vector3){1,1,1}, WHITE);
            }
            else{
                DrawModel(route5, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z},1,WHITE);

            }
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

        DrawText(TextFormat("%d $", jeu->argent), 50, 400, 30, BLACK);


        if (demandeDeFermetureWindow){
            DrawRectangle(0, 100, LARGEUR_ECRAN, 200, BLACK);
            DrawText("Voulez vous fermer la fenetre ? [Y/N]", 325, 180, 30, WHITE);
        }

        EndDrawing();
    }
    CloseWindow();
}
