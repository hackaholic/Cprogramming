#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t childpid;
    int x = 100;
    printf("x: %i\n", x);
    if((childpid = fork()) == -1) {
        printf("Error in opening child process \n");
        exit(EXIT_FAILURE);
    }

    if(childpid == 0) {
        printf("I am child process: %i\n", getpid());
        printf("Child x: %i\n", x);
        printf("Child: Changing value of x\n");
        x = 200;
        printf("Child x: %i\n", x);
    }

    if(childpid > 0) {
        printf("I am Parent process: %i\n", getpid());
        printf("Parent x: %i\n", x);
        printf("Parent: Changing value of x\n");
        x = 300;
        wait(NULL);
        printf("Parent x: %i\n", x);
    }
}