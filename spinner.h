#ifndef JACKPOT_SPINNER_H
#define JACKPOT_SPINNER_H

#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET "0123456789"
#define SIZE (sizeof(ALPHABET)/sizeof(char)-1)
#define BASETIME 120

typedef struct paramsSpinnerSt {
    uint idThread;
    uint pos;
    char value;
    pthread_mutex_t *mutex;
    pthread_cond_t *cond;
    bool *quit;
    bool run;
    pthread_cond_t *allSpinnersStopped;
} paramsSpinnerSt;

void *spinner(void *paramsSpinner);

#endif //JACKPOT_SPINNER_H
