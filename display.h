#ifndef JACKPOT_DISPLAY_H
#define JACKPOT_DISPLAY_H

#include <stdbool.h>
#include <zconf.h>
#include "spinner.h"

#define FREQUENCY 30
#define BEGIN 0
#define GAME 1
#define END 2
#define QUIT 3
#define JACKPOT 0
#define DOUBLE_WIN 1
#define LOSE 2

typedef struct paramsDisplaySt {
    bool *quit;
    paramsSpinnerSt *spinners;
    uint state;
    uint *money;
    pthread_cond_t *cond;
    uint win;
    uint lastWin;
} paramsDisplaySt;

extern void *display(void *paramsDisplay);

#endif //JACKPOT_DISPLAY_H
