//
// Created by matoran on 1/18/17.
//

#ifndef JACKPOT_SPINNER_H
#define JACKPOT_SPINNER_H

#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET "0123456789"

typedef struct paramsSpinnerSt {
    uint numberThreads;
    uint idThread;
    uint pos;
    char value;
    pthread_mutex_t *mutex;
    pthread_cond_t *cond;
    bool *quit;
} paramsSpinnerSt;

void *spinner(void *paramsThread);

#endif //JACKPOT_SPINNER_H
