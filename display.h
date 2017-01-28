//
// Created by matoran on 1/18/17.
//

#ifndef JACKPOT_DISPLAY_H
#define JACKPOT_DISPLAY_H

#include <stdbool.h>
#include <zconf.h>
#include "spinner.h"

#define FREQUENCY 30
#define BEGIN 0
#define GAME 1
#define END 2

typedef struct paramsDisplaySt {
    bool *quit;
    paramsSpinnerSt *spinners;
    uint state;
    uint *money;
} paramsDisplaySt;

extern void *display(void *paramsDisplay);

#endif //JACKPOT_DISPLAY_H
