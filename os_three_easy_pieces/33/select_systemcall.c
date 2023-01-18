/*
   Author: Kumar Shubham

   select systemcall  to monitor stdin


   The reason the select function is blocking the program execution even though it is called after the printf statement is because the select function waits until input is received from the file descriptor set, which in this case is the standard input (STDIN_FILENO). The select function blocks the program execution until input is received or until the specified timeout period has passed. This means that the program execution will not proceed until the select function receives input from the user.

It doesn't matter where the select function is placed in the code, it will always block the execution until input is received from the file descriptor set it is monitoring. In this case, the select function is monitoring the standard input and will block execution until input is received from the user.

So even if the printf statement is executed before the select function, it will still block the execution of the program until the user provides input.

*/

#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/select.h>

int main(int argc, char *argv[]) {
    fd_set rfds;
    int rc;
    char buf[100];

    while(1) {
        printf("Write Something: \n");    // new line character from printf statement causes the buffer to be flushed automatically.
        // fflush(stdout);            // try without fflush and without newline char in printf above

        FD_ZERO(&rfds);

        FD_SET(STDIN_FILENO, &rfds);

        if((rc = select(2, &rfds, NULL, NULL, NULL)) == -1 ) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        while(!FD_ISSET(STDIN_FILENO, &rfds));

        if((rc = read(STDIN_FILENO, buf, 100)) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("From stdin: %s\n", buf);
    }
    return 0;
}