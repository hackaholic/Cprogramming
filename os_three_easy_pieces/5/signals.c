#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include<sys/wait.h>


// pause and start child process

int main(int argc, char *argv[]) {
    pid_t child = fork();
    int wstatus;
    int execution_time;
    if(child == -1) {
        fprintf(stderr, "Error while creating process ...");
    }

    if(child == 0) {
        while(1) {
            printf("Doing task ...\n");
            usleep(500000);
        } 
    }

    if(child > 0) {
       
        do {
            kill(child, SIGSTOP);
            printf("Enter execution time for child: ");
            scanf("%i", &execution_time);
            kill(child, SIGCONT);
            sleep(execution_time);

        }while(execution_time > 0);

        kill(child, SIGKILL);
        waitpid(child, &wstatus, 0);
    }
}