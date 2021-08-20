#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t childpid;
    int fd;
    char p_buffer[] = {"Parent: Hello there\n"};
    char c_buffer[] = {"Child: Hello there\n"};

    // open file hello.txt
    if((fd = open("hello.txt", O_CREAT | O_WRONLY , 0660)) == -1) {
        printf("Error in opening file\n");
        exit(EXIT_FAILURE);
    }
    printf("Before fork\n");
    if((childpid = fork()) == -1) {
        printf("Error in creatig child process\n");
        exit(EXIT_FAILURE);
    }
    printf("After fork\n");
    printf("childpid: %i\n", childpid);
    if(childpid == 0) {
        printf("I am child process: %i\n", getpid());
        // sleep(10);
        write(fd, c_buffer, strlen(c_buffer));
    }

    if(childpid > 0) {
        int wstatus;
        printf("I am parent process %i\n", getpid());
        // wstatus is the status returned by child when execution fo child complete
        wait(&wstatus);
        printf("wstatus: %i\n", wstatus);
        write(fd, p_buffer, strlen(p_buffer));
    }
}