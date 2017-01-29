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
 * create mask for all threads(inherit)
 * create shared params, create threads and join them
 * @param numberWorkers
 */
void createThreads() {
    sigset_t mask;
    sigfillset(&mask);
    pthread_sigmask(SIG_SETMASK, &mask, NULL);

    pthread_t threads[NUMBER_SPINNERS];
    pthread_cond_t conditions[NUMBER_SPINNERS] = {PTHREAD_COND_INITIALIZER};

    paramsSpinnerSt paramsSpinners[NUMBER_SPINNERS];

    bool quit = false;
    uint money = MONEY;

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    uint spinnersStopped = 0;
    pthread_cond_t allSpinnersStopped = PTHREAD_COND_INITIALIZER;
    //spinners
    for (uint i = 0; i < NUMBER_SPINNERS; i++) {
        paramsSpinners[i].cond = &conditions[i];
        paramsSpinners[i].idThread = i;
        paramsSpinners[i].pos = 0;
        paramsSpinners[i].value = ALPHABET[0];
        paramsSpinners[i].quit = &quit;
        paramsSpinners[i].mutex = &mutex;
        paramsSpinners[i].run = false;
        paramsSpinners[i].allSpinnersStopped = &allSpinnersStopped;
        paramsSpinners[i].spinnersStopped = &spinnersStopped;
        int code = pthread_create(&threads[i], NULL, spinner, &paramsSpinners[i]);
        if (code != 0) {
            fprintf(stderr, "pthread_create failed!\n");
            exit(42);
        }
    }

    pthread_cond_t condController = PTHREAD_COND_INITIALIZER;

    //display
    pthread_t displayThread;
    paramsDisplaySt paramsDisplay;
    paramsDisplay.quit = &quit;
    paramsDisplay.spinners = paramsSpinners;
    paramsDisplay.state = BEGIN;
    paramsDisplay.money = &money;
    paramsDisplay.cond = &condController;
    paramsDisplay.win = LOSE;
    paramsDisplay.lastWin = 0;
    int code = pthread_create(&displayThread, NULL, display, &paramsDisplay);
    if (code != 0) {
        fprintf(stderr, "pthread_create failed!\n");
        exit(42);
    }

    //controller
    pthread_t controllerThread;
    paramsControllerSt paramsController;
    paramsController.quit = &quit;
    paramsController.spinners = paramsSpinners;
    paramsController.mutex = &mutex;
    paramsController.cond = &condController;
    paramsController.display = &paramsDisplay;
    paramsController.allSpinnersStopped = &allSpinnersStopped;
    paramsController.spinnersStopped = &spinnersStopped;
    code = pthread_create(&controllerThread, NULL, controller, &paramsController);
    if (code != 0) {
        fprintf(stderr, "pthread_create failed!\n");
        exit(42);
    }
    for (uint i = 0; i < NUMBER_SPINNERS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_join(displayThread, NULL);
    pthread_join(controllerThread, NULL);
}
