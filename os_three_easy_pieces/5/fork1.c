#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {

    printf("Starting main...\n"); 
    /*
        The first fork() call is executed. This creates a new child process. 
        Both the parent and the child continue executing from the next statement after the fork() call.

        parent  
          |     |
        child  child
          |
        child

    */
    fork();
    fork();   
    printf("i am Parent process parent pid %i, childpid: %i\n", getppid(), getpid());

    while(wait(NULL)!=-1) {
        continue;
    }
    return 0;
}