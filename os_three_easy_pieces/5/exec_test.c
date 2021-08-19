/* 
    Author: Kumar Shubham
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

<<<<<<< HEAD
    if(childpid == 0) {
        printf("I am Child Process: %i\n", getpid());
=======
    if(childpid ==0) {
        printf("I am Child Process: %i", getpid());
>>>>>>> 7a14614978929c2f35f9b3c9d43a464d7661f118
        for(i=1;i<argc && argc<=MAX_ARGS;i++) {
            myargs[i-1] = argv[i];
        }
        myargs[i-1] == NULL;
<<<<<<< HEAD
        printf("Command to run: ");
        for(i=0; i<argc-1;i++){
            printf("%s ", myargs[i]);
        }
        printf("\n");
        execvp(myargs[0], myargs);
        printf("I will not get printed\n");
    }
    if(childpid > 0) {
        printf("I am parent Process: %i\n", getpid());
        //try with and without wait system call
       pid_t child_pid = wait(NULL);
=======
        execvp(myargs[0], myargs);
        printf(" I will not get printed\n");
    }
    if(childpid > 0) {
        printf("I am parent Process: %i\n", getpid());
        // try with and without wait system call
        pid_t child_pid = wait(NULL);
>>>>>>> 7a14614978929c2f35f9b3c9d43a464d7661f118
    }
}