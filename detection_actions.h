#ifndef ECE_CITY_3B_DETECTION_ACTIONS_H
#define ECE_CITY_3B_DETECTION_ACTIONS_H

#include "messages.h"
#include "raylib.h"
#include <time.h>

typedef struct Stock_event{
    time_t temps_lancement_partie;
    time_t temps_actuel;
    
}Stock_event;

Message* detection_actions(Stock_event* stock_event);

Message* detection_temps(Stock_event* stock_event);

#endif // ECE_CITY_3B_DETECTION_ACTIONS_H