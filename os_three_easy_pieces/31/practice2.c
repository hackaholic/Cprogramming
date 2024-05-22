/*
Author: Kumar Shubham

Write a C program that demonstrates the use of semaphores to synchronize access to a shared buffer between multiple producer and consumer 
threads. 
And also handle signal and make sure all value is consumed before terminating
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/syscall.h>
#include <time.h>
#include <assert.h>
#include <signal.h>


#define MAX_PRODUCER_THREAD 2
#define MAX_CONSUMER_THREAD 3
#define MAX_BUFFER_SIZE 10


sem_t mutex;
sem_t empty;
sem_t fill;


int count = 0;
int p_count = 0;
int c_count = 0;
int buffer[MAX_BUFFER_SIZE];

static volatile int keepRunning = 1;

void sig_handler(int sig) {
    printf("Signal is Caught...\n");
    if(sig == SIGINT) {
        printf("Caught SIGINT, Exiting gracefully ...");
        keepRunning = 0;
    }
    else if (sig == SIGTERM)
    {
        printf("Caught SIGTERM, exiting gracefull ...");
        keepRunning = 0;
    }
    
    else if (sig == SIGHUP)
    {
        printf("Captured Sighup, will reload the configuration ...");
        //sleep(1);
    }

    else if (sig == SIGUSR1) {
        printf("Caught userdefined signal, SIGUSR1");
        //sleep(1);
    }


    else {
        printf("Unknown Signal caught ...");
        //sleep(1);
    }
}

int getVal() {
    int val = buffer[c_count];
    c_count = (1 + c_count) % MAX_BUFFER_SIZE;
    count--;
    return val;
}

int putVal() {
    int val = rand() % 100 + 1;
    buffer[p_count] = val;
    p_count = (1  + p_count) % MAX_BUFFER_SIZE;
    count++;
    return val;
}

void *producer(void *t) {
    int val;
    int id = (intptr_t)t;
    
    while(keepRunning) {
        sem_wait(&empty);
        sem_wait(&mutex);
        val = putVal();
        printf("Producer %i, ID: %li, value produced: %i\n", id, syscall(SYS_gettid), val);
        sem_post(&mutex);
        sem_post(&fill);
       // usleep(100000);
    }
    pthread_exit(NULL);
}

void *consumer(void *t) {
    int id = (intptr_t)t;
    int val;
    while(keepRunning) {
        sem_wait(&fill);
        sem_wait(&mutex);
        val = getVal();
        printf("Consumer %i, ID: %li, value consumed: %i\n", id, syscall(SYS_gettid), val);
        sem_post(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_t producer_thread[MAX_PRODUCER_THREAD];
    pthread_t consumer_thread[MAX_CONSUMER_THREAD];

    int i, rc;

    // signal to capture Any inrrupt
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGHUP, sig_handler);
    signal(SIGUSR1, sig_handler);

    // adding seed 
    srand(time(NULL));

    // initializing semaphore
    rc = sem_init(&mutex, 0, 1);assert(rc ==0);
    rc = sem_init(&empty, 0, MAX_BUFFER_SIZE);assert(rc == 0);
    rc = sem_init(&fill, 0, 0);

    printf("Creating Producer thread ...\n");
    for(i=0;i<MAX_PRODUCER_THREAD;i++){
        rc = pthread_create(&producer_thread[i], NULL, producer, (void *)(intptr_t)i);
        assert(rc ==0);
    }

    printf("Creating consumer thread ...\n");
    for(i=0;i<MAX_CONSUMER_THREAD;i++){
        rc = pthread_create(&consumer_thread[i], NULL, consumer, (void *)(intptr_t)i);
        assert(rc == 0);
    }

    while(keepRunning) {
        usleep(100000);
    }

    // cancelling all the thread
    printf("Stopping producer thread ....\n");
    for(i=0;i<MAX_CONSUMER_THREAD;i++) {
        rc = pthread_cancel(producer_thread[i]);assert(rc==0);
    }

    printf("Stopping consumer thread ....\n");
    for(i=0;i<MAX_PRODUCER_THREAD;i++) {
        rc = pthread_cancel(consumer_thread[i]);assert(rc==0);
    }

    printf("Witing for the thread to finish ...\n");
    for(i=0;i<MAX_PRODUCER_THREAD;i++) {
        rc = pthread_join(producer_thread[i], NULL);
        assert(rc == 0);
    }

    for(i=0;i<MAX_CONSUMER_THREAD;i++) {
        rc = pthread_join(consumer_thread[i], NULL);
        assert(rc == 0);
    }

    // destroying the semaphore
    rc = sem_destroy(&mutex);assert(rc==0);
    rc = sem_destroy(&empty);assert(rc==0);
    rc = sem_destroy(&fill);assert(rc==0);


    // Consuming remaining values:
    while(count > 0) {
        printf("Consumed value: %i\n", getVal());
    }
    printf("count: %i\n", count);
    return 0;
}
