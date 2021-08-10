#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main() {

    pid_t childpid;

    if ((childpid = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if (childpid == 0) {
        printf("I am child process, pid %d\n", getpid());
        exit(0);
    }

    if (childpid > 0) {
        printf("I am Parent process %d\n", getpid());
    }

    childpid = fork();
    printf("I am fork 1 %d\n", childpid);
    childpid = fork();
    printf("I am fork 2 %d\n", childpid);
    childpid = fork();
    printf("I am fork 3 %d\n", childpid);
    //printf("Hello World\n");
}