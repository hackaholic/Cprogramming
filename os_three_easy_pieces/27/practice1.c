/*
     Author: Kumar Shubham

Write a program that demonstrates the use of condition variables to synchronize threads.
use multiple condition variables for more complex synchronization scenarios. For example, 
you can have multiple producer threads and multiple consumer threads working with a shared buffer, 
using condition variables to manage access to the buffer.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>

#define MAX_CONSUMER_THREAD 3
#define MAX_PRODUCER_THREAD 2
#define MAX_BUFFER_SIZE 10

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;

static int p_count = 0;
static int c_count = 0;
static int count = 0;

int buffer[MAX_BUFFER_SIZE];

/*
The volatile keyword in C is used to indicate to the compiler that a variable may be changed by external factors that are not explicit in the program. 
This prevents the compiler from performing certain optimizations that assume the variable's value will not change unexpectedly.
*/

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

int putVal() {
    int rand_val = rand() % 100;
    buffer[p_count] = rand_val;
    p_count = p_count % MAX_BUFFER_SIZE + 1;
    count++;
    return rand_val;
}

int getVal () {
    int val = buffer[c_count];
    c_count = c_count % MAX_BUFFER_SIZE + 1;
    count--;
    return val;
}

void *producer() {
    int val;
    while(keepRunning) {
        pthread_mutex_lock(&mutex);
        while(count == MAX_BUFFER_SIZE) {
            pthread_cond_wait(&empty, &mutex);
        }
        val = putVal();
        printf("Producer -> %li, producer val: %i\n", syscall(SYS_gettid), val);
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
        usleep(100000);
    }
    pthread_exit(NULL);
}

void *consumer() {
    int val;
    while(keepRunning) {
        pthread_mutex_lock(&mutex);
        while(count == 0) {
            pthread_cond_wait(&full, &mutex);
        }
        val = getVal();
        printf("Consumer -> %li, consumed val: %i\n", syscall(SYS_gettid), val);
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        usleep(100000);
    }
    pthread_exit(NULL);
}


int main(int argc, char *argv[]){

    pthread_t producer_thread[MAX_PRODUCER_THREAD];
    pthread_t consumer_thread[MAX_CONSUMER_THREAD];

    int i, rc;

    printf("Starting main, pid: %i\n", getpid());
    
    // signal to capture Any inrrupt
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGHUP, sig_handler);
    signal(SIGUSR1, sig_handler);

    // initialize mutex and condition variable
    if((rc = pthread_mutex_init(&mutex, NULL)) !=0 ) {
        perror("Error While inititalizing mutex");
        exit(EXIT_FAILURE);
    }

    if ((rc = pthread_cond_init(&empty, NULL)) !=0 ) {
         perror("Error While inititalizing CV");
        exit(EXIT_FAILURE);
    }

    if ((rc = pthread_cond_init(&full, NULL)) !=0 ){
        perror("Error While inititalizing CV");
        exit(EXIT_FAILURE);
    }

    // setting the seed for random
    srand(time(NULL));

    // starting producer threads
    for(i=0;i<MAX_PRODUCER_THREAD;i++){
        if((rc = pthread_create(&producer_thread[i], NULL, producer, NULL)) != 0){
            perror("Error while creating producer thread");
            exit(EXIT_FAILURE);
        }
    }

    // start consumer thread
    for(i=0;i<MAX_CONSUMER_THREAD;i++){
        if((rc = pthread_create(&consumer_thread[i], NULL, consumer, NULL)) != 0){
            perror("Error while creating consumer thread");
            exit(EXIT_FAILURE);
        }
    }

    // wait for any intrupt else keepRunning
    while(keepRunning) {
        usleep(1000000);
    }

    printf("Stopping producer threads...\n");
    for(i=0;i<MAX_PRODUCER_THREAD;i++) {
        rc = pthread_cancel(producer_thread[i]);
        assert(rc==0);
    }

    printf("Stopping consumer threads.\n");
    for(i=0;i<MAX_CONSUMER_THREAD;i++) {
        rc = pthread_cancel(consumer_thread[i]);
        assert(rc==0);
    }

    // wait for producer and consumer to finish
    for(i=0;i<MAX_PRODUCER_THREAD;i++) {
        pthread_join(producer_thread[i], NULL);
    }

    for(i=0;i<MAX_CONSUMER_THREAD;i++){
        pthread_join(consumer_thread[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);
    return 0;

}

