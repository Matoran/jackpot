/**
 * @authors LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Management of signals
 * Language:  C
 * Date : january 2017
 */

#include <stdlib.h>
#include <stdbool.h>
#include "controller.h"
#include "threads.h"
#include <signal.h>
#include <pthread.h>

/**
 * check if the user have a jackpot, double win or lose
 * update money, last win
 * @param params of the controller
 */
void checkWin(paramsControllerSt *params) {
    int counter[SIZE] = {0};
    for (uint i = 0; i < NUMBER_SPINNERS; ++i) {
        counter[params->spinners[i].pos]++;
    }
    for (uint j = 0; j < SIZE; ++j) {
        if (counter[j] == NUMBER_SPINNERS) {
            if (*params->display->money > 1) {
                params->display->lastWin = *params->display->money / 2;
            } else {
                params->display->lastWin = 1;
            }
            *params->display->money -= params->display->lastWin;
            params->display->win = JACKPOT;
            return;
        } else if (counter[j] == NUMBER_SPINNERS - 1) {
            if ((*params->display->money - (NUMBER_SPINNERS - 1)) < *params->display->money) {
                params->display->lastWin = NUMBER_SPINNERS - 1;
            } else {
                params->display->lastWin = *params->display->money;
            }
            *params->display->money -= params->display->lastWin;
            params->display->win = DOUBLE_WIN;
            return;
        }
    }
    params->display->win = LOSE;
}

/**
 * wait signals(SIGINT, SIGQUIT, SIGTSTP, SIGALRM) and handle it
 * update game data, like money, last win and display state
 * @param paramsController
 * @return NULL
 */
void *controller(void *paramsController) {
    paramsControllerSt *params = (paramsControllerSt *) paramsController;
    sigset_t mask, maskold;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGTSTP);
    sigaddset(&mask, SIGALRM);
    pthread_sigmask(SIG_SETMASK, &mask, &maskold);

    int sig;
    int actualSpinner = 0;

    do {
        if (actualSpinner == NUMBER_SPINNERS) {
            pthread_mutex_lock(params->mutex);
            pthread_cond_wait(params->allSpinnersStopped, params->mutex);
            pthread_mutex_unlock(params->mutex);
            checkWin(params);
            params->display->state = END;
            alarm(0);
            sleep(5);
            actualSpinner = 0;
            params->display->state = BEGIN;
        }
        sigwait(&mask, &sig);
        //ctrl + c stop current spinner
        if (params->display->state == GAME && (sig == SIGINT || sig == SIGALRM)) {
            params->spinners[actualSpinner].run = false;
            actualSpinner++;
            alarm(3);
        } else if (sig == SIGTSTP) { // ctrl + z insert money
            for (int i = 0; i < NUMBER_SPINNERS; i++) {
                params->spinners[i].run = true;
                pthread_cond_signal(params->spinners[i].cond);
            }
            (*params->display->money)++;
            actualSpinner = 0;
            params->display->state = GAME;
            alarm(3);
        }
    } while (sig != SIGQUIT); //ctrl + \ quit game
    params->display->state = QUIT;
    pthread_mutex_lock(params->mutex);
    pthread_cond_wait(params->cond, params->mutex);
    pthread_mutex_unlock(params->mutex);

    *params->quit = true;
    for (int i = 0; i < NUMBER_SPINNERS; i++) {
        pthread_cond_signal(params->spinners[i].cond);
    }

    return NULL;
}
