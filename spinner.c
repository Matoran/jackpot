//
// Created by matoran on 1/18/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <memory.h>
#include <zconf.h>
#include "spinner.h"




void *spinner(void *paramsThread){
    paramsSpinnerSt *params = (paramsSpinnerSt *) paramsThread;
    struct timespec start, finish;
    double microSecondToWait = BASETIME / params->idThread;

    while(!*params->quit){
        clock_gettime(CLOCK_REALTIME, &start);

        params->pos++;
        if(params->pos >= strlen(ALPHABET)) {
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
    return NULL;
}
