/* 
    Author: Kumar Shubham
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_ARGS 5

int main(int argc, char *argv[]) {
    pid_t childpid;
    int i;
    char *myargs[MAX_ARGS];
    if(argc > MAX_ARGS) {
        printf("Max Arg allowed %i\n", MAX_ARGS);
        exit(EXIT_FAILURE);
    }
    if (( childpid = fork()) == -1) {
        printf("Error in creating child process\n");
        exit(EXIT_FAILURE);
    }

    if(childpid ==0) {
        printf("I am Child Process: %i", getpid());
        close(STDOUT_FILENO);
        open("./output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0660);
        for(i=1;i<argc && argc<=MAX_ARGS;i++) {
            myargs[i-1] = argv[i];
        }
        myargs[i-1] == NULL;
        execvp(myargs[0], myargs);
        printf("I will not get printed\n");
    }
    if(childpid > 0) {
        printf("I am parent Process: %i\n", getpid());
        // try with and without wait system call
        pid_t child_pid = wait(NULL);
    }
}