/**
 * @authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Management of threads
 * Language:  C
 * Date : january 2017
 */
#include <zconf.h>
#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include "threads.h"
#include "spinner.h"
#include "display.h"
#include "controller.h"

/**
 *
 * @param numberWorkers
 */
void createThreads(){
    sigset_t mask;
    sigfillset(&mask);
    pthread_sigmask(SIG_SETMASK, &mask, NULL);

    pthread_t threads[NUMBER_SPINNERS];
    pthread_cond_t conditions[NUMBER_SPINNERS] = {PTHREAD_COND_INITIALIZER};

    paramsSpinnerSt paramsSpinners[NUMBER_SPINNERS];

    bool quit = false;

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL);

    //spinners
    for (uint i = 0; i < NUMBER_SPINNERS; i++) {
        paramsSpinners[i].cond = &conditions[i];
        paramsSpinners[i].idThread = i+1;
        paramsSpinners[i].numberThreads = NUMBER_SPINNERS;
        paramsSpinners[i].pos = 0;
        paramsSpinners[i].value = ALPHABET[0];
        paramsSpinners[i].quit = &quit;
        paramsSpinners[i].mutex = &mutex;
        paramsSpinners[i].run = false;
        int code = pthread_create(&threads[i], NULL, spinner, &paramsSpinners[i]);
        if (code != 0) {
            fprintf(stderr, "pthread_create failed!\n");
            exit(42);
        }
    }

    //display
    pthread_t displayThread;
    paramsDisplaySt paramsDisplay;
    paramsDisplay.quit = &quit;
    paramsDisplay.spinners = paramsSpinners;
    paramsDisplay.state = BEGIN;
    pthread_create(&displayThread, NULL, display, &paramsDisplay);

    //controller
    pthread_t controllerThread;
    paramsControllerSt paramsController;
    paramsController.quit = &quit;
    paramsController.spinners = paramsSpinners;
    paramsController.state = &paramsDisplay.state;
    pthread_create(&controllerThread, NULL, controller, &paramsController);
    for (uint i = 0; i < NUMBER_SPINNERS+1; i++) {
        pthread_join(threads[i], NULL);
    }
}