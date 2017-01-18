//
// Created by matoran on 1/18/17.
//

#include "display.h"
#include <stdio.h>
#include <time.h>
#include <zconf.h>

void *display(void *paramsThread) {
    char **params = (char **) paramsThread;
    int state = GAME, win = 0;
    double microSecondToWait = 1000000.0 / FREQUENCY;
    struct timespec start, finish;
    while (1) {


        clock_gettime(CLOCK_MONOTONIC, &start);
        switch (state) {
            case BEGIN:
                printf("\e[2J");
                printf("\e[1;1H");
                printf("Insert a coin to start the game...");
                break;
            case GAME:
                printf("\e[2J");
                printf("\e[1;1H");
                printf("Game started!");
                printf("\e[3;1H");
                for (int i = 0; i < 3; ++i) {
                    printf("%c ", *params[i]);
                }
                break;
            case END:
                printf("\e[1;1H");
                printf("Game finished!");
                printf("\e[5;1H");
                switch (win) {
                    case 0:
                    case 1:
                        printf("You lost!");
                        break;
                    case 2:
                        printf("Double win!");
                        break;
                    case 3:
                        printf("JACKPOT!");
                        break;
                    default:
                        printf("error");
                }
                printf("\e[6;1H");
                printf("You won 2 coins");
                printf("\e[7;1H");
                printf("12 coins left in the machine");
                break;
        }
        clock_gettime(CLOCK_MONOTONIC, &finish);
        double elapsed = (finish.tv_sec - start.tv_sec) * 1000000;
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000.0;
        if (microSecondToWait - elapsed > 0) {
            usleep(microSecondToWait - elapsed);
        }
    }
}
