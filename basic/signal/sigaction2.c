/*
  Author: Kumar Shubham

  Here's an example that demonstrates using the sa_sigaction member of the struct sigaction to handle signals with additional information, 
  such as the address from which the signal was raised (si_addr).
*/


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>


/*

The sa_flags field in the struct sigaction is used to specify various flags that modify the behavior of the signal handler. Here are some commonly used flags:

    SA_RESTART: Causes certain system calls to be restarted if they are interrupted by a signal handler. This is useful for ensuring that certain operations, like I/O, are automatically restarted after handling a signal.

    SA_NOCLDSTOP: Prevents the generation of SIGCHLD when child processes stop (as opposed to terminating). This flag is useful for preventing the handler from being called when a child process stops.

    SA_NODEFER: Prevents the automatic blocking of the signal while its handler is executing. Normally, the signal is blocked to prevent recursive invocation of the handler.

    SA_SIGINFO: Specifies that the signal handler takes three arguments (as opposed to one for a standard signal handler). The additional arguments provide more information about the signal and the context in which it was delivered.
*/

void signal_handler(int signum, siginfo_t *s_info, void *context) {
    if(signum == SIGSEGV) {
        printf("Caught segmentation fault ...\n");
        if(s_info && s_info->si_addr) {
            printf("signal originated from addr: %p\n", s_info->si_addr);
        }
    }
}

int main() {
    struct sigaction sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_sigaction = signal_handler;
    //  The sa_flags field is set to SA_SIGINFO to indicate that the sa_sigaction member should be used instead of sa_handler.
    sa.sa_flags = SA_SIGINFO;

    /*

    */
    sigemptyset(&sa.sa_mask);

    if(sigaction(SIGSEGV, &sa, NULL) == -1) {
        perror("Error: sigaction()\n");
        exit(EXIT_FAILURE);
    }


    int *p = NULL;
    *p = 42;

    return 0;
}