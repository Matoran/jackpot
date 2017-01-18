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
#include <signal.h>


int main() {

    sigset_t mask, maskold;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGTSTP);
    pthread_sigmask(SIG_SETMASK, &mask, &maskold);

    int sig;
    int x = 0;

    do {
        sigwait(&mask, &sig);
        if (sig == SIGINT){
            if(x < NThread - 2){
                wheel.x -> stop = true;
                x++;
            }
        }else if (sig == SIGTSTP){
            for (int i = 0; i < (NThread -2); i++) {
                wheel.i -> restart = true;
            } //-> pthread_cond_broadcast(pthread_cond_t *cond) ?
        }
    } while (sig != SIGQUIT);

    for (int i = 0; i < NThread; i++) {
        thread.i -> exit = true;
    } //-> pthread_cond_broadcast(pthread_cond_t *cond) ?

    return EXIT_SUCCESS;
}
