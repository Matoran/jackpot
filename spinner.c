/**
 * @authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Management of a spinner
 * Language:  C
 * Date : january 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <zconf.h>
#include <math.h>
#include "spinner.h"
#include "threads.h"

/**
 * update spinner value every 120 / id thread(1..n) milliseconds
 * stopped until receive signal from the controller
 * @param paramsSpinner
 * @return NULL
 */
void *spinner(void *paramsSpinner) {
    paramsSpinnerSt *params = (paramsSpinnerSt *) paramsSpinner;
    struct timespec start, finish;
    double microSecondToWait = BASETIME*1000 / pow(2.0, params->idThread);
    while (!*params->quit) {
        pthread_mutex_lock(params->mutex);
        pthread_cond_wait(params->cond, params->mutex);
        pthread_mutex_unlock(params->mutex);
        while (!*params->quit && params->run) {
            clock_gettime(CLOCK_MONOTONIC, &start);
            params->pos++;
            if (params->pos >= SIZE) {
                params->pos = 0;
            }
            params->value = ALPHABET[params->pos];
            clock_gettime(CLOCK_MONOTONIC, &finish);
            double elapsed = (finish.tv_sec - start.tv_sec) * 1000000;
            elapsed += (finish.tv_nsec - start.tv_nsec) / 1000.0;
            if (microSecondToWait - elapsed > 0) {
                usleep(microSecondToWait - elapsed);
            }
        }
        pthread_mutex_lock(params->mutex);
        (*params->spinnersStopped)++;
        if(*params->spinnersStopped == NUMBER_SPINNERS){
            pthread_cond_signal(params->allSpinnersStopped);
            *params->spinnersStopped = 0;
        }
        pthread_mutex_unlock(params->mutex);
    }
    return NULL;
}
