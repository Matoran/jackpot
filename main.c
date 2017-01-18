#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include "display.h"
#include "threads.h"

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]){
    setbuf(stdout,0);
    createThreads(3);
    return EXIT_SUCCESS;
}