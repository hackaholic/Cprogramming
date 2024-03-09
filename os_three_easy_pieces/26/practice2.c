/*
Author: Kumar Shubham

Write a program that creates two threads. Each thread should print a message indicating its ID
program to pass a shared variable between the threads. Use a mutex lock to ensure that only one thread can modify the variable at a time.

*/

#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

# define LOOP 100000
// define lock and intilialize it
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *t) {

    printf("I am worker thread: %li\n", syscall(SYS_gettid));
    int *val = (int *)t;

    // aquire lock
    pthread_mutex_lock(&mutex);
    for(int i=0;i<LOOP;i++) {
        (*val)++;
    }
    // release lock

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;
    int rc;

    int i = 0;

    // create threads
    if((rc = pthread_create(&t1, NULL, worker, (void *)&i) ) != 0) {
        perror("Error While creating thread\n");
        exit(EXIT_FAILURE);
    }

    if((rc = pthread_create(&t2, NULL, worker, (void *)&i) ) != 0) {
        perror("Error While creating thread\n");
        exit(EXIT_FAILURE);
    }

    // wait for the thread to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Value of i: %i\n", i);
    pthread_mutex_destroy(&mutex);

    return 0;
}

