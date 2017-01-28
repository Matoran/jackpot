//
// Created by matoran on 1/18/17.
//

#ifndef JACKPOT_SPINNER_H
#define JACKPOT_SPINNER_H

#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET "01"
#define SIZE (sizeof(ALPHABET)/sizeof(char)-1)
#define BASETIME 1200000

typedef struct paramsSpinnerSt {
    uint numberThreads;
    uint idThread;
    uint pos;
    char value;
    pthread_mutex_t *mutex;
    pthread_cond_t *cond;
    bool *quit;
    bool run;
} paramsSpinnerSt;

void *spinner(void *paramsSpinner);

#endif //JACKPOT_SPINNER_H
