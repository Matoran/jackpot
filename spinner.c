//
// Created by matoran on 1/18/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <memory.h>
#include <zconf.h>
#include "spinner.h"



void createThreads(uint numberWorkers){
    pthread_t threads[numberWorkers];
    paramsSpinnerSt paramsThread[numberWorkers];
    bool quit = false;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL);

    for (uint i = 0; i < numberWorkers; i++) {
        paramsThread[i].idThread = i+1;
        paramsThread[i].numberThreads = numberWorkers;
        paramsThread[i].pos = 0;
        paramsThread[i].value = ALPHABET[0];
        paramsThread[i].quit = &quit;
        paramsThread[i].mutex = &mutex;
        int code = pthread_create(&threads[i], NULL, spinner, &paramsThread[i]);
        if (code != 0) {
            fprintf(stderr, "pthread_create failed!\n");
            exit(42);
        }
    }
}

void *spinner(void *paramsThread){
    paramsSpinnerSt *params = (paramsSpinnerSt *) paramsThread;
    struct timespec start, finish;
    double microSecondToWait = 120 / params->idThread;

    while(!params->quit){
        if(params->pos < strlen(ALPHABET)) {
            params->pos++;
        }else{
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
