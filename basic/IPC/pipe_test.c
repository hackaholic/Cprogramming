#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_BUFF 100
#define SLEEP_TIME 60

int interrupt = 0;
void signal_handler(int sig) {
    printf("Caught Signal -> %d\n", sig);
    switch (sig) {
        case SIGCONT:
            interrupt = 1;
        case SIGTERM:
            break;
        default:
            break;
    }
}

int main() {
    char buff[MAX_BUFF];
    int nbytes;
    int fd[3];
    pid_t childpid;
    struct tm* tmp;
    time_t t;

    pipe(fd);

    if ( (childpid = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if (childpid == 0) {
        // capture signal
        signal(SIGCONT, signal_handler);
        signal(SIGTERM, signal_handler);
        char timestr[50];
        printf("I am child process, pid: %d, ppid: %d, pgid: %d\n", getpid(), getppid(), getpgid(getpid()));
        t = time(NULL);
        tmp = gmtime(&t);
        //strftime(timestr, 50, "%d-%m-%y %H:%M:%S", tmp);
        //sleep(SLEEP_TIME);
        if (!interrupt) {
            pause();
        }
        else {
        strcpy(timestr, asctime(tmp));
        printf("%s", timestr);
        close(fd[0]);
        write(fd[1], timestr, strlen(timestr));
        }
    }

    if (childpid > 0) {
        int wstatus;
        pid_t child_p;
        child_p = waitpid(-1, &wstatus, 0);         // try with wait and without wait
        printf("child pid: %d, returned status: %d\n", child_p, wstatus);
        printf("I am parent process pid: %d, ppid: %d, pgid: %d\n", getpid(), getppid(), getpgid(getpid()));
        close(fd[1]);
        nbytes = read(fd[0], buff, MAX_BUFF);
        if (nbytes) {
            printf("No of bytes read from child: %d\n", nbytes);
            fprintf(stdout, "Time from child: %s\n", buff);
        }
    }

}