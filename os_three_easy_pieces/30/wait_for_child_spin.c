/*

Author: Kumar Shubham

Wait for child using spin approach

*/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#include<assert.h>
#include<sys/syscall.h>


volatile int ready = 0;

void *child(void *arg) {
    printf("I am child: %lu\n", syscall(SYS_gettid));
    sleep(2);
    ready = 1;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    time_t now;
    struct tm *local_time;
    pthread_t th_child;
    int rc;

    now = time(NULL);
    local_time = localtime(&now);

    printf("Main starts here: %s", asctime(local_time));

    rc = pthread_create(&th_child, NULL, child, NULL);assert(rc==0);
    while(ready==0) {
        printf("Waiting for child to complete\n");
        sleep(1);
    }
    pthread_join(th_child, NULL);

    printf("Main ends here\n");
    return 0;
}


