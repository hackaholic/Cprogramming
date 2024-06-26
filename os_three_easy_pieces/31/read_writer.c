/*
    Author: Kumar Shubham

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

//
// Your code goes in the structure and functions below
//

typedef struct __rwlock_t {
    sem_t r_lock;
    sem_t w_lock;
    int readers;
} rwlock_t;


void rwlock_init(rwlock_t *rw) {
    sem_init(&rw->r_lock, 0, 1);
    sem_init(&rw->w_lock, 0, 1);
    rw->readers = 0;
}

void rwlock_acquire_readlock(rwlock_t *rw) {
    sem_wait(&rw->r_lock);
    rw->readers++;
    if(rw->readers == 1) {
        sem_wait(&rw->w_lock);
    }
    sem_post(&rw->r_lock);
}

void rwlock_release_readlock(rwlock_t *rw) {
    sem_wait(&rw->r_lock);
    rw->readers--;

    if(rw->readers == 0)
        sem_post(&rw->w_lock);
    
    sem_post(&rw->r_lock);
}

void rwlock_acquire_writelock(rwlock_t *rw) {
    sem_wait(&rw->w_lock);
    //sem_wait(&rw->r_lock);
}

void rwlock_release_writelock(rwlock_t *rw) {
    sem_post(&rw->w_lock);
    //sem_post(&rw->r_lock);
}

//
// Don't change the code below (just use it!)
// 

int loops;
int value = 0;

rwlock_t lock;

void *reader(void *arg) {
    printf("I am readers\n");
    int i;
    for (i = 0; i < loops; i++) {
	    rwlock_acquire_readlock(&lock);
	    printf("read %d\n", value);
	    rwlock_release_readlock(&lock);
    }
    return NULL;
}

void *writer(void *arg) {
    printf("I am writer\n");
    int i;
    for (i = 0; i < loops; i++) {
	    rwlock_acquire_writelock(&lock);
	    value++;
	    printf("write %d\n", value);
	    rwlock_release_writelock(&lock);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    assert(argc == 4);
    int num_readers = atoi(argv[1]);
    int num_writers = atoi(argv[2]);
    loops = atoi(argv[3]);

    pthread_t pr[num_readers], pw[num_writers];

    rwlock_init(&lock);

    printf("begin\n");

    int i;
    for (i = 0; i < num_readers; i++)
	    pthread_create(&pr[i], NULL, reader, NULL);
    for (i = 0; i < num_writers; i++)
	    pthread_create(&pw[i], NULL, writer, NULL);

    for (i = 0; i < num_readers; i++)
	    pthread_join(pr[i], NULL);
    for (i = 0; i < num_writers; i++)
	    pthread_join(pw[i], NULL);

    printf("end: value %d\n", value);

    return 0;
}

