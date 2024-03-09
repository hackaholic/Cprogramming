/*

*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


static volatile int keepRunning = 1;
void sig_handler(int sig) {
    printf("Signal is Caught...\n");
    if(sig == SIGINT) {
        printf("Caught SIGINT, Exiting gracefully ...");
        keepRunning = 0;
    }
    else if (sig == SIGTERM)
    {
        printf("Caught SIGTERM, exiting gracefull ...");
        keepRunning = 0;
    }
    
    else if (sig == SIGHUP)
    {
        printf("Captured Sighup, will reload the configuration ...");
        //sleep(1);
    }

    else if (sig == SIGUSR1) {
        printf("Caught userdefined signal, SIGUSR1");
        //sleep(1);
    }


    else {
        printf("Unknown Signal caught ...");
        //sleep(1);
    }
    
    
}


