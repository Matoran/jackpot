
#ifndef JACKPOT_CONTROLLER_H
#define JACKPOT_CONTROLLER_H

#include "spinner.h"

typedef struct paramsControllerSt {
    bool *quit;
    paramsSpinnerSt *spinners;
    uint *state;
} paramsControllerSt;

void *controller(void *paramsController);

#endif //JACKPOT_CONTROLLER_H
