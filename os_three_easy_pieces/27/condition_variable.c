/*
Author: Kumar Shubham

Condition variable practice

*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#include<errno.h>
#include<assert.h>

#define SLEEP_TIME 5

pthread_mutex_t lock;
pthread_cond_t cond;
static volatile int ready = 0;

void *producer(void *arg) {

    printf("Producer: Applying lock\n");
    pthread_mutex_lock(&lock);
    printf("Producer: Sleeping for %i sec\n", SLEEP_TIME);
    sleep(SLEEP_TIME);
    printf("Producer: Ready = 1\n");
    ready = 1;
    printf("Producer: Signal ...\n");
    pthread_cond_signal(&cond);
    printf("Producer: Unlock\n");
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

void *consumer(void *arg) {

    printf("Consumer: Applying Lock\n");
    pthread_mutex_lock(&lock);
    
    printf("Consumer: Contition wait ...\n");
    while(ready == 0) {
        pthread_cond_wait(&cond, &lock);
    }

    printf("Consumer: ready is 1\n");
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);

}

int main(int argc, char *argv[]) {
    pthread_t t1,t2;
    time_t now;
    struct tm *local_time;
    int rc;
    now = time(NULL);
    local_time = localtime(&now);
    printf("Main Starts here\n");
    fprintf(stdout, "Date: %s", asctime(local_time));

    if((pthread_mutex_init(&lock, NULL)) != 0){
        fprintf(stderr, "Error in initializing lock\n");
        exit(EXIT_FAILURE);
    }
    if((pthread_cond_init(&cond, NULL)) != 0) {
        fprintf(stderr, "Error in initializing condition varibale\n");
        exit(EXIT_FAILURE);
    }

    rc = pthread_create(&t1, NULL, producer, NULL); assert(rc==0);
    rc = pthread_create(&t2, NULL, consumer, NULL); assert(rc==0);

    rc = pthread_join(t1, NULL); assert(rc==0);
    rc = pthread_join(t2, NULL); assert(rc==0);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}

