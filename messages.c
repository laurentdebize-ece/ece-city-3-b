#include "messages.h"
#include <stdlib.h>

Message* creer_message(int type1, int type2, int type3, int type4){
    Message* message = malloc(sizeof(Message));
    message->type[0] = type1;
    message->type[1] = type2;
    message->type[2] = type3;
    message->type[3] = type4;
    return message;
}