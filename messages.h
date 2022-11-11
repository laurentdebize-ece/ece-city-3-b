#ifndef ECE_CITY_3B_MESSAGES_H
#define ECE_CITY_3B_MESSAGES_H

typedef struct {
    int type[4];
} Message;

Message* creer_message(int type1, int type2, int type3, int type4);

#define AUCUN 0

// type 1 : 

#define CONSTRUIRE_MAISON 1
#define CONSTRUIRE_ROUTE 2
#define CONSTRUIRE_CENTRALE 3
#define CONSTRUIRE_CHATEAU_EAU 4

#define DETRUIRE_MAISON 5
#define DETRUIRE_ROUTE 6
#define DETRUIRE_CENTRALE 7
#define DETRUIRE_CHATEAU_EAU 8

#define CYCLE_FINI 9
#define NOUVELLE_SECONDE 10

#define QUITTER 11
#define NOUVELLE_PARTIE 12
#define CHARGER_PARTIE 13
#define QUITTER_PARTIE 14
#define SAUVEGARDER_PARTIE 15

// type 2 :

//CONSTRUIRE_MAISON /ROUTE /CENTRALE /CHATEAU_EAU
//position x de la construction

//DETRUIRE_MAISON /CENTRALE /CHATEAU_EAU
//numero de la construction

//DETRUIRE_ROUTE
//position x de la construction

//type 3 :

//CONSTRUIRE_MAISON /ROUTE /CENTRALE /CHATEAU_EAU
//position y de la construction

//DETRUIRE_ROUTE
//position y de la construction

//type 4 :

//CONSTRUIRE_CENTRALE /CHATEAU_EAU
#define HORIZONTAL 1



#endif // ECE_CITY_3B_MESSAGES_H