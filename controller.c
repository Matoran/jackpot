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


uint checkWin(paramsControllerSt *pSt) {
    int counter[SIZE] = {0};
    for (uint i = 0; i < NUMBER_SPINNERS; ++i) {
        counter[pSt->spinners[i].pos]++;
    }
    for (uint j = 0; j < SIZE; ++j) {
        if(counter[j] == NUMBER_SPINNERS){
            return JACKPOT;
        }else if(counter[j] == NUMBER_SPINNERS-1){
            return DOUBLE_WIN;
        }
    }
    return LOSE;
}

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
                    params->display->win = checkWin(params);
                    switch (params->display->win){
                        case JACKPOT:
                            if(*params->display->money > 1){
                                params->display->lastWin = *params->display->money / 2;
                            }else{
                                params->display->lastWin = 1;
                            }
                            params->display->money -= params->display->lastWin;

                            break;
                        case DOUBLE_WIN:
                            if((*params->display->money - (NUMBER_SPINNERS-1)) < *params->display->money){
                                params->display->lastWin = NUMBER_SPINNERS-1;
                            }else{
                                params->display->lastWin = *params->display->money;
                            }
                            *params->display->money -= params->display->lastWin;
                            break;
                    }
                    params->display->state = END;
                    sleep(5);
                    params->display->state = BEGIN;
                }
            }
        }else if (sig == SIGTSTP){ // ctrl + z insert money
            for (int i = 0; i < NUMBER_SPINNERS; i++) {
                params->spinners[i].run = true;
                pthread_cond_signal(params->spinners[i].cond);
            }
            actualSpinner = 0;
            (*params->display->money)++;
            params->display->state = GAME;
        }else if(sig == SIGUSR1){

        }
    } while (sig != SIGQUIT); //ctrl + \ quit game
    params->display->state = QUIT;
    pthread_mutex_lock(params->mutex);
    pthread_cond_wait(params->cond, params->mutex);
    pthread_mutex_unlock(params->mutex);

    *params->quit = true;
    for (int i = 0; i < NUMBER_SPINNERS; i++) {
        pthread_cond_signal(params->spinners[i].cond);
        //thread.i -> exit = true;
    } //-> pthread_cond_broadcast(pthread_cond_t *cond) ?

    return NULL;
}
