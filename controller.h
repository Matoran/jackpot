#ifndef JACKPOT_CONTROLLER_H
#define JACKPOT_CONTROLLER_H

#include "spinner.h"
#include "display.h"

typedef struct paramsControllerSt {
    bool *quit;
    paramsSpinnerSt *spinners;
    pthread_mutex_t *mutex;
    pthread_cond_t *cond;
    paramsDisplaySt *display;
} paramsControllerSt;

void *controller(void *paramsController);

#endif //JACKPOT_CONTROLLER_H
