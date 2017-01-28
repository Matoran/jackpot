/**
 * @authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Management of a spinner
 * Language:  C
 * Date : january 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <memory.h>
#include <zconf.h>
#include "spinner.h"


void *spinner(void *paramsSpinner) {
    paramsSpinnerSt *params = (paramsSpinnerSt *) paramsSpinner;
    struct timespec start, finish;
    double microSecondToWait = BASETIME / params->idThread;

    while (!*params->quit) {
        pthread_mutex_lock(params->mutex);
        pthread_cond_wait(params->cond, params->mutex);
        pthread_mutex_unlock(params->mutex);
        while (!*params->quit && params->run) {
            clock_gettime(CLOCK_REALTIME, &start);

            params->pos++;
            if (params->pos >= sizeof(ALPHABET)/sizeof(char)-1) {
                params->pos = 0;
            }
            clock_gettime(CLOCK_REALTIME, &finish);
            double elapsed = (finish.tv_sec - start.tv_sec) * 1000000;
            elapsed += (finish.tv_nsec - start.tv_nsec) / 1000.0;
            if (microSecondToWait - elapsed > 0) {
                usleep(microSecondToWait - elapsed);
            }
            params->value = ALPHABET[params->pos];
        }

    }
    return NULL;
}
