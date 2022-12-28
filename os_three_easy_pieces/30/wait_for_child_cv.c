/*
  Author: Kumar Shubham

  Wait for child , using condition Variable
*/

#include<stdio.h>
#include<pthread.h>
#include<assert.h>
#include<time.h>
#include<unistd.h>
#include<sys/syscall.h>


volatile int ready = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *child(void *arg) {

    pthread_mutex_lock(&lock);
    printf("I am child: %lu\n", syscall(SYS_gettid));
    sleep(5);
    ready = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}


int main(int argc, char * argv[]) {
    time_t now;
    struct tm *local_time;
    pthread_t th_child;
    int rc;

    now = time(NULL);
    local_time = localtime(&now);
    printf("Main starts here: %s", asctime(local_time));
    rc = pthread_create(&th_child, NULL, child, NULL);assert(rc==0);
    while(ready == 0) {
        printf("Waiting for child ...\n");
        pthread_cond_wait(&cond, &lock);
        printf("Waiting Over ....\n");
    }
    pthread_join(th_child, NULL);
    printf("Main Ends here\n");

    return 0;
}