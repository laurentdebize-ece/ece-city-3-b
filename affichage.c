#include "affichage.h"
#include <stdio.h>
#include <raylib.h>
#include "compteur.h"
#include <stdlib.h>
#include <time.h>
#include "construction_destruction.h"
#include "fichier.h"

void choixM(Jeu** jeu, bool lancer){
    bool exit = false;
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

        DrawTextureEx(Simcityflou, (Vector2){scrollingBack, 0 }, 0.0f, 1.2f, WHITE);
        DrawTextureEx(Simcityflou, (Vector2){Simcityflou.width * 2 , 20 }, 0.0f, 1.2f, WHITE);


        DrawTextureEx(Choix, (Vector2){63,50 }, 0.0f, 0.6f, WHITE);
        if((GetMousePosition().x >= 204) && (GetMousePosition().x <=  485) && (GetMousePosition().y >= 334) && (GetMousePosition().y <= 414)){
            DrawTextureEx(Capitaliste, (Vector2){63,50 }, 0.0f, 0.6f, WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                (*jeu)->mode_jeu = MODE_CAPITALISTE;
                affichageMapRaylib(*jeu, lancer);
            }
        }
        if((GetMousePosition().x >= 780) && (GetMousePosition().x <=  1061) && (GetMousePosition().y >= 334) && (GetMousePosition().y <= 414)){
            DrawTextureEx(Communiste, (Vector2){63,50 }, 0.0f, 0.6f, WHITE);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                (*jeu)->mode_jeu = MODE_COMMUNISTE;
                affichageMapRaylib(*jeu, lancer);
            }
        }


        EndDrawing();
    }
    UnloadTexture(Choix);
    UnloadTexture(Capitaliste);
    UnloadTexture(Communiste);
    CloseWindow();
}


void menu1(Jeu* jeu){
    // Pour longueur et largeur: screenWidth 2000, screenHeight 1450
    float scrollingBack = 0.0f;
    bool exit = false;
    bool regle = false;
    bool regle2 = false;
    bool debut = true;
    bool lancer = false;


    InitWindow(LARGEUR_ECRAN, HAUTEUR_ECRAN, "menu");
    Image simcity = LoadImage("../image/simcity.png");
    Image logo = LoadImage("../image/logoSimcity.png");
    Image jouer = LoadImage("../image/logo.png");
    Image jouer2 = LoadImage("../image/logoclick.png");
    Image regles = LoadImage("../image/relges.png");
    Image regles2 = LoadImage("../image/regles2.png");
    Image sauvegarde = LoadImage("../image/sauvegarder.png");
    Image sauvegarde2 = LoadImage("../image/sauvegarder2.png");
    Image rules = LoadImage("../image/rules.png");
    Image fondRules = LoadImage("../image/rules2.png");
    Image rules2 = LoadImage("../image/fondRules.png");
    Image suivant2 = LoadImage("../image/suivant.png");
    Image retour2 = LoadImage("../image/retour.png");
    Image suivant = LoadImage("../image/retour1.png");
    Image retour = LoadImage("../image/suivant1.png");

    Texture2D Simcity = LoadTextureFromImage(simcity);
    Texture2D Logo = LoadTextureFromImage(logo);
    Texture2D Jouer = LoadTextureFromImage(jouer);
    Texture2D Jouer2 = LoadTextureFromImage(jouer2);
    Texture2D Regles = LoadTextureFromImage(regles);
    Texture2D Regles2 = LoadTextureFromImage(regles2);
    Texture2D Sauvegarde = LoadTextureFromImage(sauvegarde);
    Texture2D Sauvegarde2 = LoadTextureFromImage(sauvegarde2);
    Texture2D Rules = LoadTextureFromImage(rules);
    Texture2D Rules2 = LoadTextureFromImage(rules2);
    Texture2D FondRules = LoadTextureFromImage(fondRules);
    Texture2D Suivant2 = LoadTextureFromImage(suivant2);
    Texture2D Retour2 = LoadTextureFromImage(retour2);
    Texture2D Retour = LoadTextureFromImage(retour);
    Texture2D Suivant = LoadTextureFromImage(suivant);

    UnloadImage(simcity);
    UnloadImage(logo);
    UnloadImage(jouer);
    UnloadImage(jouer2);
    UnloadImage(regles2);
    UnloadImage(regles);
    UnloadImage(sauvegarde2);
    UnloadImage(sauvegarde);
    UnloadImage(rules);
    UnloadImage(rules2);
    UnloadImage(fondRules);
    UnloadImage(suivant);
    UnloadImage(suivant2);
    UnloadImage(retour);
    UnloadImage(retour2);


    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        scrollingBack -= 0.1f;
        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -simcity.width * 10) scrollingBack = 0;

        BeginDrawing();
        ClearBackground(WHITE);


        if(debut){
            DrawTextureEx(Simcity, (Vector2){scrollingBack, 0 }, 0.0f, 1.2f, WHITE);
            DrawTextureEx(Simcity, (Vector2){simcity.width * 2 , 20 }, 0.0f, 1.2f, WHITE);

            DrawTextureEx(Logo, (Vector2){130,40 }, 0.0f, 1.1f, WHITE);

            DrawTextureEx(Jouer, (Vector2){350,160 }, 0.0f, 0.3f, WHITE);
            if((GetMousePosition().x >= 522) && (GetMousePosition().x <= 744) && (GetMousePosition().y >= 291) && (GetMousePosition().y <= 353)){
                DrawTextureEx(Jouer2, (Vector2){350,160 }, 0.0f, 0.3f, WHITE);
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    choixM(&jeu, lancer);
                }
            }
            DrawTextureEx(Sauvegarde, (Vector2){350,310 }, 0.0f, 0.3f, WHITE);
            if((GetMousePosition().x >= 522) && (GetMousePosition().x <= 744) && (GetMousePosition().y >= 441) && (GetMousePosition().y <= 503)){
                DrawTextureEx(Sauvegarde2, (Vector2){350,310 }, 0.0f, 0.3f, WHITE);
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    lancer = true;
                    affichageMapRaylib(jeu, lancer);
                }
            }
            DrawTextureEx(Regles, (Vector2){350,460 }, 0.0f, 0.3f, WHITE);
            if((GetMousePosition().x >= 522) && (GetMousePosition().x <= 744) && (GetMousePosition().y >= 591) && (GetMousePosition().y <= 653)){
                DrawTextureEx(Regles2, (Vector2){350,460 }, 0.0f, 0.3f, WHITE);
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    debut = false;
                    regle2 = false;
                    regle = true;
                }
            }
        }
        //DrawText(TextFormat("Position souris : x = %d y = %d", GetMouseX(), GetMouseY()), 10, 15, 20, BLACK);
        if(regle){
            DrawTextureEx(FondRules,(Vector2){0,0},0,0.9f,WHITE);
            DrawTextureEx(Rules, (Vector2){120,50 }, 0.0f, 0.55f, WHITE);
            DrawTextureEx(Retour,(Vector2){25,-15},0.0f,0.2f,WHITE);
            DrawTextureEx(Suivant,(Vector2){890,-15},0.0f,0.2f,WHITE);
            DrawText(TextFormat("Position souris : x = %d y = %d", GetMouseX(), GetMouseY()), 10, 15, 20, BLACK);
            if((GetMousePosition().x >= 140) && (GetMousePosition().x <= 293) && (GetMousePosition().y >= 80) && (GetMousePosition().y <= 125)){
                DrawTextureEx(Retour2,(Vector2){25,-15},0.0f,0.2f,WHITE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    regle = false;
                    regle2 = false;
                    debut = true;
                }
            }
            if((GetMousePosition().x >= 1005) && (GetMousePosition().x <=1160) && (GetMousePosition().y >= 80) && (GetMousePosition().y <= 125)){
                DrawTextureEx(Suivant2,(Vector2){890,-15},0.0f,0.2f,WHITE);
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    regle = false;
                    debut = false;
                    regle2 = true;
                }
            }
        }

        if(regle2){
            DrawTextureEx(FondRules,(Vector2){0,0},0,0.9f,WHITE);
            DrawTextureEx(Rules2, (Vector2){110,110 }, 0.0f, 0.55f, WHITE);
            DrawTextureEx(Retour,(Vector2){25,-15},0.0f,0.2f,WHITE);
            if((GetMousePosition().x >= 140) && (GetMousePosition().x <=293) && (GetMousePosition().y >= 80) && (GetMousePosition().y <= 125)){
                DrawTextureEx(Retour2,(Vector2){25,-15},0.0f,0.2f,WHITE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    regle2 = false;
                    debut = false;
                    regle = true;
                }
            }
        }


        //DrawText("jouer", 940, 710, 100, RED);
        //si bouton dans la zone du bouton jouer d'une autre couleur

        EndDrawing();
    }

    UnloadTexture(Simcity);
    UnloadTexture(Logo);
    UnloadTexture(Jouer);
    UnloadTexture(Jouer2); // a finir
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

void affichageMapRaylib(Jeu* jeu, bool lancer){
   // InitWindow(LARGEUR_ECRAN, HAUTEUR_ECRAN, "ECE-City");

    srand(time(NULL)) ;
    int posX = 0;
    int posY = 0;
    bool maison = false;
    bool chateau = false;
    bool centrale = false;
    bool road = false;
    bool destruction  = false;
    bool niveauElec = false;
    bool niveauEau = false;
    bool niveauNormal = true;
    bool save = false;
    bool demandeDeSave = false;


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
    Model sol = LoadModel("../3D/ground_grass.obj");
    Model herbe1 = LoadModel("../3D/grass.obj");
    Model herbe2 = LoadModel("../3D/grass_large.obj");
    Model herbe3 = LoadModel("../3D/grass_leafs.obj");
    Model maison1 = LoadModel("../3D/house_type02.obj");
    Model cabane = LoadModel("../3D/tent_detailedClosed.obj");
    Model immeuble = LoadModel("../3D/large_buildingC.obj");
    Model gratteCiel = LoadModel("../3D/skyscraperF.obj");
    Model chateauEau = LoadModel("../3D/chateauEau.glb");
    Model usine = LoadModel("../3D/usine.glb");
    Model route1 = LoadModel("../3D/road_bendSidewalk.obj");
    Model route2 = LoadModel("../3D/road_crossroad.obj");
    Model route3 = LoadModel("../3D/road_end.obj");
    Model route4 = LoadModel("../3D/road_intersectionPath.obj");
    Model route5 = LoadModel("../3D/road_straight.obj");
    Model ruine = LoadModel("../3D/woodStructure.obj");
    Model terrainVague = LoadModel("../3D/terrain.obj");









    Image icone_maison = LoadImage("../image/maison.png");
    Image icone_chateau = LoadImage("../image/chateau.png");
    Image icone_centrale = LoadImage("../image/usine.png");
    Image icone_reseau_eau = LoadImage("../image/eau.png");
    Image icone_reseau_elec = LoadImage("../image/elect.png");
    Image icone_detruire_maison = LoadImage("../image/destructionMaison.png");
    Image icone_detruire_batiment = LoadImage("../image/destruction.png");
    Image icone_route = LoadImage("../image/route.png");
    Image eauBouton = LoadImage("../image/eauBouton.png");
    Image elecBouton = LoadImage("../image/electriciteBouton.png");
    Image habitantBouton = LoadImage("../image/habitantBouton.png");
    Image temps = LoadImage("../image/temps.png");
    Image sauvegarde = LoadImage("../image/sauvegarde.png");
    Image sauvegardeOui = LoadImage("../image/sauvegarderOui.png");
    Image sauvegarderNon = LoadImage("../image/sauvegarderNon.png");
    Image quitter = LoadImage("../image/quitter.png");

    Image icone_maisonO = LoadImage("../image/maisonOmbre.png");
    Image icone_chateauO = LoadImage("../image/chateauOmbre.png");
    Image icone_centraleO = LoadImage("../image/usineOmbre.png");
    Image icone_reseau_eauO = LoadImage("../image/eauOmbre.png");
    Image icone_reseau_elecO = LoadImage("../image/electOmbre.png");
    Image icone_detruire_maisonO = LoadImage("../image/destructionMaisonOmbre.png");
    Image icone_detruire_batimentO = LoadImage("../image/destructionOmbre.png");
    Image icone_routeO = LoadImage("../image/routeO.png");
    Image dollars = LoadImage("../image/dollars.png");
    Image icone_M = LoadImage("../image/M.png");
    Image icone_M_Ombre = LoadImage("../image/MOmbre.png");
    Texture2D Sauvegarde = LoadTextureFromImage(sauvegarde);
    Texture2D SauvegardeOui = LoadTextureFromImage(sauvegardeOui);
    Texture2D SauvegarderNon = LoadTextureFromImage(sauvegarderNon);
    Texture2D Quitter = LoadTextureFromImage(quitter);



    Texture2D Icone_maison = LoadTextureFromImage(icone_maison);
    Texture2D Icone_chateau = LoadTextureFromImage(icone_chateau);
    Texture2D Icone_centrale = LoadTextureFromImage(icone_centrale);
    Texture2D Icone_reseau_eau = LoadTextureFromImage(icone_reseau_eau);
    Texture2D Icone_reseau_elec = LoadTextureFromImage(icone_reseau_elec);
    Texture2D Icone_destruction_maison = LoadTextureFromImage(icone_detruire_maison);
    Texture2D Icone_destruction_bat = LoadTextureFromImage(icone_detruire_batiment);
    Texture2D Icone_maisonO = LoadTextureFromImage(icone_maisonO);
    Texture2D Icone_chateauO = LoadTextureFromImage(icone_chateauO);
    Texture2D Icone_centraleO = LoadTextureFromImage(icone_centraleO);
    Texture2D Icone_reseau_eauO = LoadTextureFromImage(icone_reseau_eauO);
    Texture2D Icone_reseau_elecO = LoadTextureFromImage(icone_reseau_elecO);
    Texture2D Icone_destruction_maisonO = LoadTextureFromImage(icone_detruire_maisonO);
    Texture2D Icone_destruction_batO = LoadTextureFromImage(icone_detruire_batimentO);
    Texture2D Icone_route = LoadTextureFromImage(icone_route);
    Texture2D Icone_routeO = LoadTextureFromImage(icone_routeO);
    Texture2D EauBouton = LoadTextureFromImage(eauBouton);
    Texture2D ElecBouton = LoadTextureFromImage(elecBouton);
    Texture2D HabitantBouton = LoadTextureFromImage(habitantBouton);
    Texture2D Dollars = LoadTextureFromImage(dollars);
    Texture2D Temps = LoadTextureFromImage(temps);
    Texture2D Icone_M = LoadTextureFromImage(icone_M);
    Texture2D Icone_M_Ombre = LoadTextureFromImage(icone_M_Ombre);


    UnloadImage(icone_maison);
    UnloadImage(icone_chateau);
    UnloadImage(icone_centrale);
    UnloadImage(icone_reseau_eau);
    UnloadImage(icone_reseau_elec);
    UnloadImage(icone_detruire_maison);
    UnloadImage(icone_detruire_batiment);
    UnloadImage(icone_maisonO);
    UnloadImage(icone_chateauO);
    UnloadImage(icone_centraleO);
    UnloadImage(icone_reseau_eauO);
    UnloadImage(icone_reseau_elecO);
    UnloadImage(icone_detruire_maisonO);
    UnloadImage(icone_detruire_batimentO);
    UnloadImage(icone_route);
    UnloadImage(icone_routeO);
    UnloadImage(eauBouton);
    UnloadImage(elecBouton);
    UnloadImage(habitantBouton);
    UnloadImage(dollars);
    UnloadImage(temps);
    UnloadImage(icone_M);
    UnloadImage(icone_M_Ombre);
    UnloadImage(sauvegarde);
    UnloadImage(sauvegardeOui);
    UnloadImage(sauvegarderNon);
    UnloadImage(quitter);


    SetCameraMode(camera, CAMERA_FREE);   // mode de camera libre
    SetExitKey(KEY_NULL);
    bool demandeDeFermetureWindow = false;   // booléen demandant à fermer la fenetre
    bool fermetureWindow = false;    // booléen permettant de quitter la fenetre
    SetTargetFPS(60);  // notre jeu tournera en 60 fps



    while (!fermetureWindow) {

        detection_temps(jeu);

        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)){
            demandeDeFermetureWindow = true;
        }
        if (demandeDeFermetureWindow == true){

            if (IsKeyPressed(KEY_Y)){
                fermetureWindow = true;
                sauvegarderJeu(jeu);
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

        if((GetMousePosition().x >= 50) && (GetMousePosition().x <= 100) && (GetMousePosition().y >= 214) && (GetMousePosition().y <= 273)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                centrale = false;
                chateau = false;
                road = false;
                destruction = false;
                niveauElec = false;
                niveauEau = false;
                niveauNormal = true;
                maison = true;
            }
        }
        if(maison){
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                int i,j;
                for(i = 0; i < TAILLE_MAP_X;i++){
                    for(j = 0; j < TAILLE_MAP_Y;j++){
                        if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 && collision.point.x  <= cases[i][j].x + 0.5  && collision.point.x >= cases[i][j].x - 0.5){
                            if (construire(jeu, TYPE_MAISON,i,j,0)) {
                                jeu->maisons[jeu->nb_maisons - 1].position.pos_x= cases[i][j].x + 1;
                                jeu->maisons[jeu->nb_maisons - 1].position.pos_y= collision.point.y;
                                jeu->maisons[jeu->nb_maisons - 1].position.pos_z= cases[i][j].z - 1;
                                maj_totale(jeu);
                            }
                        }

                    }
                }
            }
        }


        if((GetMousePosition().x >= 45) && (GetMousePosition().x <= 105) && (GetMousePosition().y >= 315) && (GetMousePosition().y <= 373)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                maison = false;
                chateau = false;
                road = false;
                destruction = false;
                niveauElec = false;
                niveauEau = false;
                niveauNormal = true;
                centrale = true;

            }
        }
        if(centrale){
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                int i,j;
                for(i = 0; i < TAILLE_MAP_X;i++){
                    for(j = 0; j < TAILLE_MAP_Y;j++){
                        if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 && collision.point.x  <= cases[i][j].x + 0.5  && collision.point.x >= cases[i][j].x - 0.5){
                            if (construire(jeu, TYPE_CENTRALE,i,j,0)) {
                                jeu->batiments[jeu->nb_centrales + jeu->nb_chateau_eau - 1].position.pos_x= cases[i][j].x + 2.5;
                                jeu->batiments[jeu->nb_centrales + jeu->nb_chateau_eau - 1].position.pos_y= collision.point.y;
                                jeu->batiments[jeu->nb_centrales + jeu->nb_chateau_eau - 1].position.pos_z= cases[i][j].z - 1.5;
                                maj_totale(jeu);
                            }
                        }
                    }


                }
            }
        }

        if((GetMousePosition().x >= 60) && (GetMousePosition().x <= 90) && (GetMousePosition().y >= 415) && (GetMousePosition().y <= 473)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                maison = false;
                centrale = false;
                road = false;
                destruction = false;
                niveauElec = false;
                niveauEau = false;
                niveauNormal = true;
                chateau = true;
            }
        }
        if(chateau){
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                int i,j;
                for(i = 0; i < TAILLE_MAP_X;i++){
                    for(j = 0; j < TAILLE_MAP_Y;j++){
                        if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 && collision.point.x  <= cases[i][j].x + 0.5  && collision.point.x >= cases[i][j].x - 0.5){
                            if (construire(jeu, TYPE_CHATEAU_EAU,i,j,0)) {
                                jeu->batiments[jeu->nb_centrales + jeu->nb_chateau_eau - 1].position.pos_x= cases[i][j].x;
                                jeu->batiments[jeu->nb_centrales + jeu->nb_chateau_eau - 1].position.pos_y= collision.point.y;
                                jeu->batiments[jeu->nb_centrales + jeu->nb_chateau_eau - 1].position.pos_z= cases[i][j].z;
                                maj_totale(jeu);
                            }
                        }
                    }

                }
            }
        }

        if((GetMousePosition().x >= 45) && (GetMousePosition().x <= 105) && (GetMousePosition().y >= 515) && (GetMousePosition().y <= 573)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                maison = false;
                centrale = false;
                chateau = false;
                destruction = false;
                niveauElec = false;
                niveauEau = false;
                niveauNormal = true;
                road = true;
            }
        }
        if(road){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                int i,j;
                for(i = 0; i < TAILLE_MAP_X;i++){
                    for(j = 0; j < TAILLE_MAP_Y;j++){
                        if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 && collision.point.x  <= cases[i][j].x + 0.5  && collision.point.x >= cases[i][j].x - 0.5){
                            if (construire(jeu, TYPE_ROUTE,i,j,0)) {
                                jeu->routes[jeu->nb_routes - 1].position.pos_x= cases[i][j].x;
                                jeu->routes[jeu->nb_routes - 1].position.pos_y= collision.point.y;
                                jeu->routes[jeu->nb_routes - 1].position.pos_z= cases[i][j].z;
                                maj_totale(jeu);
                            }
                        }
                    }

                }
            }
        }
        if((GetMousePosition().x >= 45) && (GetMousePosition().x <= 105) && (GetMousePosition().y >= 615) && (GetMousePosition().y <= 673)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                maison = false;
                centrale = false;
                chateau = false;
                road = false;
                niveauElec = false;
                niveauEau = false;
                niveauNormal = true;
                destruction = true;
            }
        }
        if(destruction){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                int i,j;
                for(i = 0; i < TAILLE_MAP_X;i++) {
                    for (j = 0; j < TAILLE_MAP_Y; j++) {
                        if (collision.point.z <= cases[i][j].z + 0.5 && collision.point.z >= cases[i][j].z - 0.5 &&
                            collision.point.x <= cases[i][j].x + 0.5 && collision.point.x >= cases[i][j].x - 0.5) {
                            detruire(jeu,i,j);
                            maj_totale(jeu);
                        }
                    }
                }
            }
        }

        if((GetMousePosition().x >= 710) && (GetMousePosition().x <=763) && (GetMousePosition().y >= 24) && (GetMousePosition().y <= 73)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                maison = false;
                centrale = false;
                chateau = false;
                road = false;
                niveauEau = false;
                destruction = false;
                niveauNormal = false;
                niveauElec = true;
            }
        }
        if(niveauElec){
            DrawModel(sol,positionCubeSol,TAILLE_PLATEAU,DARKGRAY);
            dessinerCases(cases);
            DrawCubeWires(positionContourCarte, TAILLE_MAP_Y, 0, TAILLE_MAP_X, BLACK);
            // DrawGrid(50, 1);

            for(int i = 0; i < 1000; i++){
                DrawModel(herbe1, positionHerbe1[i], 1, DARKGRAY);
                i = i + 1;
            }
            for(int i = 0; i < 1000; i++){
                DrawModel(herbe2, positionHerbe2[i], 1, DARKGRAY);
                i = i + 1;
            }
            for(int i = 0; i < 1000; i++){
                DrawModel(herbe3, positionHerbe3[i], 1, DARKGRAY);
                i = i + 1;
            }


            for(int i = 0; i < jeu->nb_maisons; i++){
                switch(jeu->maisons[i].niveau){
                    case NIVEAU_TERRAIN_VAGUE:
                        DrawModel(terrainVague, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y + 0.01,jeu->maisons[i].position.pos_z},3,DARKGRAY);
                        break;
                    case NIVEAU_RUINE:
                        DrawModel(ruine, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,DARKGRAY);
                        DrawModel(terrainVague, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y + 0.01,jeu->maisons[i].position.pos_z},3,DARKGRAY);
                        break;
                    case NIVEAU_CABANE:
                        DrawModel(cabane, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,DARKGRAY);
                        break;
                    case NIVEAU_MAISON:
                        DrawModel(maison1, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,DARKGRAY);
                        break;
                    case NIVEAU_IMMEUBLE:
                        DrawModel(immeuble, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2.7,DARKGRAY);
                        break;
                    case NIVEAU_GRATTE_CIEL:
                        DrawModel(gratteCiel, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,DARKGRAY);
                        break;
                }
            }


            for(int i = 0; i < jeu->nb_centrales+jeu->nb_chateau_eau; i++){
                switch (jeu->batiments[i].type_batiment) {
                    case TYPE_CHATEAU_EAU:
                        DrawModel(chateauEau, (Vector3){jeu->batiments[i].position.pos_x,jeu->batiments[i].position.pos_y,jeu->batiments[i].position.pos_z},0.002f,DARKGRAY);
                        break;
                    case TYPE_CENTRALE:
                        DrawModel(usine, (Vector3){jeu->batiments[i].position.pos_x,jeu->batiments[i].position.pos_y,jeu->batiments[i].position.pos_z},0.003f,YELLOW);
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
                    DrawModel(route2, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z},1,YELLOW);

                }
                else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_EST]){
                    DrawModelEx(route4, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 180.0f, (Vector3){1,1,1}, YELLOW);
                }
                else if(routes_a_cote[ROUTE_OUEST] && routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_EST]){
                    DrawModelEx(route4, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, -90.0f, (Vector3){1,1,1}, YELLOW);
                }
                else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_OUEST] && routes_a_cote[ROUTE_EST]){
                    DrawModelEx(route4, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 90.0f, (Vector3){1,1,1}, YELLOW);
                }
                else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_OUEST]){
                    DrawModel(route4, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z},1,YELLOW);
                }
                else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_NORD]){
                    DrawModel(route5, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z},1,YELLOW);
                }
                else if(routes_a_cote[ROUTE_EST] && routes_a_cote[ROUTE_OUEST]){
                    DrawModelEx(route5, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 90.0f, (Vector3){1,1,1}, YELLOW);
                }
                else if(routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_OUEST]){
                    DrawModelEx(route1, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 0.0f, (Vector3){1,1,1}, YELLOW);
                }
                else if(routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_EST]){
                    DrawModelEx(route1, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, -90.0f, (Vector3){1,1,1}, YELLOW);
                }
                else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_OUEST]){
                    DrawModelEx(route1, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 90.0f, (Vector3){1,1,1}, YELLOW);
                }
                else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_EST]){
                    DrawModelEx(route1, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, -180.0f, (Vector3){1,1,1}, YELLOW);
                }
                else if(routes_a_cote[ROUTE_SUD]){
                    DrawModelEx(route3, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 0.0f, (Vector3){1,1,1}, YELLOW);
                }
                else if(routes_a_cote[ROUTE_NORD]){
                    DrawModelEx(route3, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 180.0f, (Vector3){1,1,1}, YELLOW);
                }
                else if(routes_a_cote[ROUTE_OUEST]){
                    DrawModelEx(route3, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, -90.0f, (Vector3){1,1,1}, YELLOW);
                }
                else if(routes_a_cote[ROUTE_EST]){
                    DrawModelEx(route3, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 90.0f, (Vector3){1,1,1}, YELLOW);
                }
                else{
                    DrawModel(route5, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z},1,YELLOW);

                }
            }
        }
        if((GetMousePosition().x >= 540) && (GetMousePosition().x <=593) && (GetMousePosition().y >= 24) && (GetMousePosition().y <= 73)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                maison = false;
                centrale = false;
                chateau = false;
                road = false;
                destruction = false;
                niveauElec = false;
                niveauNormal = false;
                niveauEau = true;
            }
        }
        if(niveauEau){
            DrawModel(sol,positionCubeSol,TAILLE_PLATEAU,DARKGRAY);
            dessinerCases(cases);
            DrawCubeWires(positionContourCarte, TAILLE_MAP_Y, 0, TAILLE_MAP_X, BLACK);
            // DrawGrid(50, 1);

            for(int i = 0; i < 1000; i++){
                DrawModel(herbe1, positionHerbe1[i], 1, DARKGRAY);
                i = i + 1;
            }
            for(int i = 0; i < 1000; i++){
                DrawModel(herbe2, positionHerbe2[i], 1, DARKGRAY);
                i = i + 1;
            }
            for(int i = 0; i < 1000; i++){
                DrawModel(herbe3, positionHerbe3[i], 1, DARKGRAY);
                i = i + 1;
            }


            for(int i = 0; i < jeu->nb_maisons; i++){
                switch(jeu->maisons[i].niveau){
                    case NIVEAU_TERRAIN_VAGUE:
                        DrawModel(terrainVague, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y + 0.01,jeu->maisons[i].position.pos_z},3,DARKGRAY);
                        break;
                    case NIVEAU_RUINE:
                        DrawModel(ruine, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,DARKGRAY);
                        DrawModel(terrainVague, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y + 0.01,jeu->maisons[i].position.pos_z},3,DARKGRAY);
                        break;
                    case NIVEAU_CABANE:
                        DrawModel(cabane, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,DARKGRAY);
                        break;
                    case NIVEAU_MAISON:
                        DrawModel(maison1, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,DARKGRAY);
                        break;
                    case NIVEAU_IMMEUBLE:
                        DrawModel(immeuble, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2.7,DARKGRAY);
                        break;
                    case NIVEAU_GRATTE_CIEL:
                        DrawModel(gratteCiel, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,DARKGRAY);
                        break;
                }
            }


            for(int i = 0; i < jeu->nb_centrales+jeu->nb_chateau_eau; i++){
                switch (jeu->batiments[i].type_batiment) {
                    case TYPE_CHATEAU_EAU:
                        DrawModel(chateauEau, (Vector3){jeu->batiments[i].position.pos_x,jeu->batiments[i].position.pos_y,jeu->batiments[i].position.pos_z},0.002f,SKYBLUE );

                        break;
                    case TYPE_CENTRALE:
                        DrawModel(usine, (Vector3){jeu->batiments[i].position.pos_x,jeu->batiments[i].position.pos_y,jeu->batiments[i].position.pos_z},0.003f,DARKGRAY);
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
                    DrawModel(route2, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z},1,SKYBLUE);

                }
                else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_EST]){
                    DrawModelEx(route4, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 180.0f, (Vector3){1,1,1}, SKYBLUE);
                }
                else if(routes_a_cote[ROUTE_OUEST] && routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_EST]){
                    DrawModelEx(route4, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, -90.0f, (Vector3){1,1,1}, SKYBLUE);
                }
                else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_OUEST] && routes_a_cote[ROUTE_EST]){
                    DrawModelEx(route4, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 90.0f, (Vector3){1,1,1}, SKYBLUE);
                }
                else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_OUEST]){
                    DrawModel(route4, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z},1,SKYBLUE);
                }
                else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_NORD]){
                    DrawModel(route5, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z},1,SKYBLUE);
                }
                else if(routes_a_cote[ROUTE_EST] && routes_a_cote[ROUTE_OUEST]){
                    DrawModelEx(route5, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 90.0f, (Vector3){1,1,1}, SKYBLUE);
                }
                else if(routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_OUEST]){
                    DrawModelEx(route1, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 0.0f, (Vector3){1,1,1}, SKYBLUE);
                }
                else if(routes_a_cote[ROUTE_NORD] && routes_a_cote[ROUTE_EST]){
                    DrawModelEx(route1, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, -90.0f, (Vector3){1,1,1}, SKYBLUE);
                }
                else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_OUEST]){
                    DrawModelEx(route1, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 90.0f, (Vector3){1,1,1}, SKYBLUE);
                }
                else if(routes_a_cote[ROUTE_SUD] && routes_a_cote[ROUTE_EST]){
                    DrawModelEx(route1, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, -180.0f, (Vector3){1,1,1}, SKYBLUE);
                }
                else if(routes_a_cote[ROUTE_SUD]){
                    DrawModelEx(route3, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 0.0f, (Vector3){1,1,1}, SKYBLUE);
                }
                else if(routes_a_cote[ROUTE_NORD]){
                    DrawModelEx(route3, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 180.0f, (Vector3){1,1,1}, SKYBLUE);
                }
                else if(routes_a_cote[ROUTE_OUEST]){
                    DrawModelEx(route3, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, -90.0f, (Vector3){1,1,1}, SKYBLUE);
                }
                else if(routes_a_cote[ROUTE_EST]){
                    DrawModelEx(route3, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z}, axeRotation, 90.0f, (Vector3){1,1,1}, SKYBLUE);
                }
                else{
                    DrawModel(route5, (Vector3){jeu->routes[i].position.pos_x,jeu->routes[i].position.pos_y,jeu->routes[i].position.pos_z},1,SKYBLUE);

                }
            }

        }
        if((GetMousePosition().x >= 627) && (GetMousePosition().x <=675) && (GetMousePosition().y >= 21) && (GetMousePosition().y <= 71)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                maison = false;
                centrale = false;
                chateau = false;
                road = false;
                destruction = false;
                niveauElec = false;
                niveauEau = false;
                niveauNormal = true;
            }
        }
        if(niveauNormal){
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


            for(int i = 0; i < jeu->nb_maisons; i++){
                switch(jeu->maisons[i].niveau){
                    case NIVEAU_TERRAIN_VAGUE:
                        DrawModel(terrainVague, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y + 0.01,jeu->maisons[i].position.pos_z},3,WHITE);
                        break;
                    case NIVEAU_RUINE:
                        DrawModel(ruine, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,WHITE);
                        DrawModel(terrainVague, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y + 0.01,jeu->maisons[i].position.pos_z},3,WHITE);
                        break;
                    case NIVEAU_CABANE:
                        DrawModel(cabane, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,WHITE);
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
                        DrawModel(chateauEau, (Vector3){jeu->batiments[i].position.pos_x,jeu->batiments[i].position.pos_y,jeu->batiments[i].position.pos_z},0.002f,WHITE);
                        break;
                    case TYPE_CENTRALE:
                        DrawModel(usine, (Vector3){jeu->batiments[i].position.pos_x,jeu->batiments[i].position.pos_y,jeu->batiments[i].position.pos_z},0.003f,WHITE);
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

        }

        if(lancer){
            FILE *fichierJeu = fopen("../caracteristiques.txt", "r");
            int argentPred, eau, elec, nbRoute, nbMaison, nbCentrale, nbChateau;

            fscanf(fichierJeu, "%d ", &argentPred);
            fscanf(fichierJeu, "%d ", &nbMaison);
            fscanf(fichierJeu, "%d ", &nbRoute);
            fscanf(fichierJeu, "%d ", &nbCentrale);
            fscanf(fichierJeu, "%d ", &nbChateau);

            // detecter les routes
            for(int i = 0; i < jeu->nb_routes; i++){
                fscanf(fichierJeu, "%d ", &jeu->routes[i].pos_x);
                fscanf(fichierJeu, "%d ", &jeu->routes[i].pos_y);
                fscanf(fichierJeu, "%f ", &jeu->routes[i].position.pos_x);
                fscanf(fichierJeu, "%f ", &jeu->routes[i].position.pos_y);
                fscanf(fichierJeu, "%f ", &jeu->routes[i].position.pos_z);

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
                fscanf(fichierJeu, "\n");
            }
            // detecter les maisons + routes adjacentes
            for (int i = 0; i < nbMaison; i++) {
                fscanf(fichierJeu, "%d ", &jeu->maisons[i].pos_x);
                fscanf(fichierJeu, "%d ", &jeu->maisons[i].pos_y);
                fscanf(fichierJeu, "%d ", &jeu->maisons[i].niveau);
                fscanf(fichierJeu, "%d ", &jeu->maisons[i].habitants);
                fscanf(fichierJeu, "%d ", &jeu->maisons[i].eau);
                fscanf(fichierJeu, "%d ", &jeu->maisons[i].electricite);
                fscanf(fichierJeu, "%f ", &jeu->maisons[i].position.pos_x);
                fscanf(fichierJeu, "%f ", &jeu->maisons[i].position.pos_y);
                fscanf(fichierJeu, "%f ", &jeu->maisons[i].position.pos_z);

                switch(jeu->maisons[i].niveau){
                    case NIVEAU_TERRAIN_VAGUE:
                        DrawModel(terrainVague, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y + 0.01,jeu->maisons[i].position.pos_z},3,WHITE);
                        break;
                    case NIVEAU_RUINE:
                        DrawModel(ruine, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,WHITE);
                        DrawModel(terrainVague, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y + 0.01,jeu->maisons[i].position.pos_z},3,WHITE);
                        break;
                    case NIVEAU_CABANE:
                        DrawModel(cabane, (Vector3){jeu->maisons[i].position.pos_x,jeu->maisons[i].position.pos_y,jeu->maisons[i].position.pos_z},2,WHITE);
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
                fscanf(fichierJeu, "\n");

            }
            // detecter les centrales et leur routes adjacentes
            for (int i = 0; i < nbCentrale + nbChateau; i++) {
                fscanf(fichierJeu, "%d ", &jeu->batiments[i].pos_x);
                fscanf(fichierJeu, "%d ", &jeu->batiments[i].pos_y);
                fscanf(fichierJeu, "%d ", &jeu->batiments[i].type_batiment);
                fscanf(fichierJeu, "%d ", &jeu->batiments[i].capacite);
                fscanf(fichierJeu, "%f ", &jeu->batiments[i].position.pos_x);
                fscanf(fichierJeu, "%f ", &jeu->batiments[i].position.pos_y);
                fscanf(fichierJeu, "%f ", &jeu->batiments[i].position.pos_z);

                int horizontal;
                fscanf(fichierJeu, "%d", &horizontal);
                // pour faire fonctionner le bouleen est reussir a lire le fichier quand meme car on print dans le fichier un int 0/1
                if (horizontal == 1) {
                    jeu->batiments[i].horizontal = true;
                } else {
                    jeu->batiments[i].horizontal = false;
                }
                switch (jeu->batiments[i].type_batiment) {
                    case TYPE_CHATEAU_EAU:
                        DrawModel(chateauEau, (Vector3){jeu->batiments[i].position.pos_x,jeu->batiments[i].position.pos_y,jeu->batiments[i].position.pos_z},0.002f,WHITE);
                        break;
                    case TYPE_CENTRALE:
                        DrawModel(usine, (Vector3){jeu->batiments[i].position.pos_x,jeu->batiments[i].position.pos_y,jeu->batiments[i].position.pos_z},0.003f,WHITE);
                        break;
                }
                fscanf(fichierJeu, "\n");

            }
            jeu->argent = argentPred;
        }

        EndMode3D();
        DrawText(TextFormat("Position souris : x = %d y = %d", GetMouseX(), GetMouseY()), 10, 15, 20, BLACK);



        if (collision.hit)
        {
            int ypos = 10;
            DrawText(TextFormat("Distance camera: %3.2f", collision.distance), 980, ypos, 10, BLACK);
            DrawText(TextFormat("Position souris sur plateau : x = %3.2f y = %3.2f z = %3.2f", collision.point.x, collision.point.y, collision.point.z), 980, ypos + 15, 10, BLACK);
        }

        DrawTextureEx(Dollars, (Vector2){20, 140 }, 0.0f, 0.06f, WHITE);
        DrawText(TextFormat("%d ", jeu->argent), 30, 162, 20, WHITE);
        DrawTextureEx(HabitantBouton,(Vector2){20, 100 }, 0.0f, 0.06f, WHITE);
        DrawText(TextFormat("%d ", jeu->population), 30, 122, 20, WHITE);
        DrawTextureEx(EauBouton,(Vector2){20, 60 }, 0.0f, 0.06f, WHITE);
        DrawText(TextFormat("%d ", jeu->eau), 30, 82, 20, WHITE);
        DrawTextureEx(ElecBouton,(Vector2){20, 20 }, 0.0f, 0.06f, WHITE);
        DrawText(TextFormat("%d ", jeu->electricite), 30, 42, 20, WHITE);
        DrawTextureEx(Temps,(Vector2){1150, 660 }, 0.0f, 0.06f, WHITE);
        DrawText(TextFormat("%d ", jeu->temps - 1669560780 -27700 -100), 1160, 682, 20, WHITE);


        DrawRectangleGradientV(20,200,115,500,DARKGREEN,GREEN);
        DrawRectangleLines(20,200,115,500,BLACK);
        DrawRectangleGradientV(525,15,250,65,DARKGREEN,GREEN);
        DrawRectangleLines(525,15,250,65,BLACK);

        DrawTextureEx(Icone_maison,(Vector2){-20, 190}, 0.0f, 0.1f, WHITE);
        if((GetMousePosition().x >= 50) && (GetMousePosition().x <= 100) && (GetMousePosition().y >= 214) && (GetMousePosition().y <= 273)){
            DrawTextureEx(Icone_maisonO, (Vector2){-20,190 }, 0.0f, 0.1f, WHITE);
        }

        DrawTextureEx(Icone_centrale,(Vector2){-20, 290}, 0.0f, 0.1f, WHITE);
        if((GetMousePosition().x >= 45) && (GetMousePosition().x <= 105) && (GetMousePosition().y >= 315) && (GetMousePosition().y <= 373)){
            DrawTextureEx(Icone_centraleO, (Vector2){-20,290 }, 0.0f, 0.1f, WHITE);
        }

        DrawTextureEx(Icone_chateau,(Vector2){-20, 390 }, 0.0f, 0.1f, WHITE);
        if((GetMousePosition().x >= 60) && (GetMousePosition().x <= 90) && (GetMousePosition().y >= 415) && (GetMousePosition().y <= 473)){
            DrawTextureEx(Icone_chateauO, (Vector2){-20,390 }, 0.0f, 0.1f, WHITE);
        }

        DrawTextureEx(Icone_route,(Vector2){-20, 490 }, 0.0f, 0.1f, WHITE);
        if((GetMousePosition().x >= 45) && (GetMousePosition().x <= 105) && (GetMousePosition().y >= 515) && (GetMousePosition().y <= 573)){
            DrawTextureEx(Icone_routeO, (Vector2){-20,490 }, 0.0f, 0.1f, WHITE);
        }

        DrawTextureEx(Icone_destruction_bat,(Vector2){-20, 590 }, 0.0f, 0.1f, WHITE);
        if((GetMousePosition().x >= 45) && (GetMousePosition().x <= 105) && (GetMousePosition().y >= 615) && (GetMousePosition().y <= 673)){
            DrawTextureEx(Icone_destruction_batO, (Vector2){-20,590 }, 0.0f, 0.1f, WHITE);
        }

        DrawTextureEx(Icone_reseau_eau,(Vector2){470,-5},0,0.1f,WHITE);
        if((GetMousePosition().x >= 540) && (GetMousePosition().x <=593) && (GetMousePosition().y >= 24) && (GetMousePosition().y <= 73)){
            DrawTextureEx(Icone_reseau_eauO,(Vector2){470,-5},0,0.1f,WHITE);
        }

        DrawTextureEx(Icone_reseau_elec,(Vector2){640,-5},0,0.1f,WHITE);
        if((GetMousePosition().x >= 710) && (GetMousePosition().x <=763) && (GetMousePosition().y >= 24) && (GetMousePosition().y <= 73)){
            DrawTextureEx(Icone_reseau_elecO,(Vector2){640,-5},0,0.1f,WHITE);
        }

        DrawTextureEx(Icone_M,(Vector2){580,5},0,0.075f,WHITE);
        if((GetMousePosition().x >= 627) && (GetMousePosition().x <=675) && (GetMousePosition().y >= 21) && (GetMousePosition().y <= 71)){
            DrawTextureEx(Icone_M_Ombre,(Vector2){580,5},0,0.075f,WHITE);
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
