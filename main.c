#include "construction_destruction.h"
#include "initialisation_liberation.h"
#include "detection_actions.h"
#include "debug.h"
#include "affichage.h"
#include <stdio.h>

int main() {
    printf("test SIMCITY !\n");

    Jeu jeu = initialisation_jeu();

    Stock_event stock_event;
    stock_event.temps_lancement_partie = time(NULL);
    Message* message = NULL;
    while (time(NULL) - stock_event.temps_lancement_partie < 60)
    {
        message = detection_actions(&stock_event);
        if (message->type[0] == CYCLE_FINI){
            DEBUG_PRINT("cycle fini\n");
        }
        else if (message->type[0] == NOUVELLE_SECONDE){
            DEBUG_PRINT("nouvelle seconde ")
            DEBUG_PRINT_INT(stock_event.temps_actuel - stock_event.temps_lancement_partie)
            DEBUG_PRINT("\n")
        }
        free(message);
        message = NULL;
    }
        liberation_jeu(&jeu);
    return 0;
}