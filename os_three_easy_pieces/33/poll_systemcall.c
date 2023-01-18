/*
 Author: Kumar Shubham

 poll system call practice

*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<errno.h>
#include<poll.h>

#define MAX_FDS 1
#define MAX_BUFF 100

int main(int argc, char *argv[]) {

    int rc;
    struct pollfd pfds[MAX_FDS];

    int timeout = -1;

    // add values to pollfd structure
    pfds[0].fd = STDIN_FILENO; 
    pfds[0].events = POLLIN;

    printf("Write something: ");
    fflush(stdout);
    
    if((rc = poll(pfds, 1, timeout) == -1)) {      // timeout -1 will block execution indefinitely
        perror("poll");
        exit(EXIT_FAILURE);
    }

    while(1) {
        if(pfds[0].revents & POLLIN) {
            char buff[MAX_BUFF];
            if((rc = read(STDIN_FILENO, buff, MAX_BUFF) == -1)) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            printf("From stdin: %s\n", buff);
        }
    }

    return 0;

}




