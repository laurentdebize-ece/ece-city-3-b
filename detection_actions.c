#include "detection_actions.h"
#include "debug.h"

Message* detection_actions(Stock_event* stock_event){
    Message* message = NULL;

    message = detection_temps(stock_event);

    if (message == NULL){
        message = creer_message(AUCUN,AUCUN,AUCUN,AUCUN);
    }
    return message;
}

Message* detection_temps(Stock_event* stock_event){
    if(stock_event->temps_actuel != time(NULL)){
        stock_event->temps_actuel = time(NULL);
        if ((stock_event->temps_actuel - stock_event->temps_lancement_partie)%15 == 0){
            return creer_message(CYCLE_FINI, AUCUN, AUCUN, AUCUN);
        }
        else{
            return creer_message(NOUVELLE_SECONDE, AUCUN, AUCUN, AUCUN);
        }
    }
    else{
        return NULL;
    }
}