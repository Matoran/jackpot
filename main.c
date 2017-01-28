#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <signal.h>
#include "display.h"
#include "threads.h"

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(){
    createThreads();
    return EXIT_SUCCESS;
}