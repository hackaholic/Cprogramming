/*
     Author: Kumar Shubham
      We'll create a scenario where multiple threads are trying to access a shared resource (in this case, the console for printing),
       and we'll use semaphores to control access to this resource.
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <semaphore.h>
#include <errno.h>
#include <assert.h>

#define MAX_THREADS 5

static int count = 1;

sem_t mutex;

void *child(void *t) {
    int val = (intptr_t) t;
    printf("I am thread %i,  ID: %li\n", val, syscall(SYS_gettid));
    
    // enter the critial section
    sem_wait(&mutex);
    count *= 2;
    sem_post(&mutex);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t pthread[MAX_THREADS];
    int i, rc;
    // initalize the semaphore
    sem_init(&mutex, 0, 1);

    // create thread
    for(i=0;i<MAX_THREADS;i++){
        if((rc = pthread_create(&pthread[i], NULL, child, (void *) (intptr_t)i)) != 0) {
            perror("Error while creating thread ...");
            exit(EXIT_FAILURE);
        }
    }

    // wait for the thread to finish
    for(i=0;i<MAX_THREADS;i++){
        rc = pthread_join(pthread[i], NULL);
        assert(rc == 0);
    }

    rc = sem_destroy(&mutex);
    assert(rc == 0);

    printf("Final count value: %i\n", count);

    return 0;
}


