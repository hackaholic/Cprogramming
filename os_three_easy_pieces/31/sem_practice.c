/* 
   Author: Kumar Shubham
*/

#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<assert.h>
#include<error.h>
#include<pthread.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/syscall.h>

sem_t m;

void *child(void *arg) {
    printf("I am child; thread_id: %lu\n", syscall(SYS_gettid));
    sleep(2);
    sem_post(&m);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    time_t now;
    struct tm *local_time;
    pthread_t t1;
    int rc;

    now = time(NULL);
    local_time = localtime(&now);
    printf("Main Starts here: %s", asctime(local_time));
    sem_init(&m, 0, 0);
    rc = pthread_create(&t1, NULL, child, NULL);assert(rc==0);
    printf("Waiting for child ...\n");
    sem_wait(&m);

    pthread_join(t1, NULL);

    printf("Main ends here\n.");

    return 0;
}