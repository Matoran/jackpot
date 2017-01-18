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
    sigqddset(&mask, SIGTSTP);
    pthread_sigmask(SIG_SETMASK, &mask, &maskold);

    int sig;
    int x = 0;

    do {
        sigwait(&mask, &sig);
        if (sig == SIGINT){
            if(x < NThread - 2){
                wheel.x -> stop = true;
            }
        }else if (sig == SIGTSTP){
            for (int i = 0; i < NThread; i++) {
                wheel.i -> restart = true;
            }
        }
            puts("Be strong, I whispered to my wifi signal!");
    } while (sig != SIGQUIT);

    for (int i = 0; i < NThread; i++) {
        thread.i -> exit = true;
    }

    return EXIT_SUCCESS;
}
