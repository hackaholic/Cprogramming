/*
  Author: Kumar Shubham

  capture ctrl-C using sigaction

  man sigaction
  for different signal and their discripton -> man 7 signal
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>


void signal_handler(int signum) {
    switch(signum) {
        case SIGINT:
            printf("caught CTRL-C\n");
            printf("Doing clenup before aborting....\n");
            break;
        
        case SIGUSR1:
            printf("caught USER SIGNAL\n");
            printf("Reloading config...\n");
            break;
    }

    exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[]) {
    struct sigaction sa;

    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;

    /*
       The sigemptyset function is used to initialize a signal set to empty,
       meaning that no signals are included in the set.
       This function is typically used to initialize the sa_mask field of the struct sigaction to
       ensure that no signals are blocked when the signal handler is executed. Blocking signals 
       can prevent the handler from being interrupted by other signals, 
       which can be important for ensuring the correct behavior of the handler.
    */
    sigemptyset(&sa.sa_mask);

    // adding signal to sigaction to monitor
    if(sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error: sigaction");
        exit(EXIT_FAILURE);
    }

    if(sigaction(SIGQUIT, &sa, NULL) == -1) {
        perror("Error: sigaction");
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("Doing some task....\n");
        sleep(1);
    }

    return 0;
}