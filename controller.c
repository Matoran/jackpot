/**
 * @authors LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Management of signals
 * Language:  C
 * Date : january 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include "controller.h"
#include <signal.h>

static void handler(int signum) {
    char msg[] = "SIGINT received! Aborted.\n";
    write(STDOUT_FILENO, msg, strlen(msg));
    _exit(EXIT_SUCCESS);
}

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
            if(x < ){
                wheel.x -> stop = true;
            }
        }else if (sig == SIGTSTP){
            for (int i = 0; i < ; i++) {
                wheel.i -> restart = true;
            }
        }
            puts("Be strong, I whispered to my wifi signal!");
    } while (sig != SIGQUIT);

    for (int i = 0; i < ; i++) {
        thread.i -> exit = true;
    }

    return EXIT_SUCCESS;
}
