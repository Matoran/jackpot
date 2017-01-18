//
// Created by matoran on 1/18/17.
//

#include <zconf.h>
#include <pthread.h>
#include <stdio.h>
#include "threads.h"
#include "spinner.h"
#include "display.h"


void createThreads(uint numberWorkers){
    pthread_t threads[numberWorkers+1];
    char *spinners[numberWorkers];
    paramsSpinnerSt paramsThread[numberWorkers];
    bool quit = false;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL);

    for (uint i = 0; i < numberWorkers; i++) {
        paramsThread[i].idThread = i+1;
        paramsThread[i].numberThreads = numberWorkers;
        paramsThread[i].pos = 0;
        paramsThread[i].value = ALPHABET[0];
        spinners[i] = &(paramsThread[i].value);
        paramsThread[i].quit = &quit;
        paramsThread[i].mutex = &mutex;
        int code = pthread_create(&threads[i], NULL, spinner, &paramsThread[i]);
        if (code != 0) {
            fprintf(stderr, "pthread_create failed!\n");
            exit(42);
        }
    }
    pthread_create(&threads[numberWorkers], NULL, display, &spinners);

    for (uint i = 0; i < numberWorkers+1; i++) {
        pthread_join(threads[i], NULL);
    }
}