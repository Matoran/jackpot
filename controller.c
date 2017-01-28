/**
 * @authors LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Management of signals
 * Language:  C
 * Date : january 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "controller.h"
#include "threads.h"
#include "spinner.h"
#include "display.h"
#include <signal.h>
#include <pthread.h>


void *controller(void *paramsController) {
    paramsControllerSt *params = (paramsControllerSt*)paramsController;
    sigset_t mask, maskold;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGTSTP);
    pthread_sigmask(SIG_SETMASK, &mask, &maskold);

    int sig;
    int actualSpinner = 0;

    do {
        sigwait(&mask, &sig);
        //ctrl + c stop current spinner
        if (sig == SIGINT){
            if(actualSpinner < NUMBER_SPINNERS){
                params->spinners[actualSpinner].run = false;
                actualSpinner++;
                if(actualSpinner == NUMBER_SPINNERS){
                    *params->state = END;
                }
            }
        }else if (sig == SIGTSTP){ // ctrl + z insert money
            for (int i = 0; i < NUMBER_SPINNERS; i++) {
                params->spinners[i].run = true;
                pthread_cond_signal(params->spinners[i].cond);
            }
            actualSpinner = 0;
            (*params->money)++;
            *params->state = GAME;
        }else if(sig == SIGUSR1){

        }
    } while (sig != SIGQUIT); //ctrl + \ quit game
    *params->quit = true;
    for (int i = 0; i < NUMBER_SPINNERS; i++) {
        pthread_cond_signal(params->spinners[i].cond);
        //thread.i -> exit = true;
    } //-> pthread_cond_broadcast(pthread_cond_t *cond) ?

    return NULL;
}
