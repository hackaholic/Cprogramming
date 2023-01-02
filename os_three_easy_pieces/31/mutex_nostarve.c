#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

#define MAX_THREAD 5

int loop = 5;

typedef struct __ns_mutex_t {
    sem_t lock;
    sem_t s;
    int turn;
}ns_mutex_t;

ns_mutex_t nsmutex;

void ns_mutex_init(ns_mutex_t *m) {
    sem_init(&m->lock, 0, 1);
    sem_init(&m->s, 0, 0);
    m->turn = 0;
}

void ns_mutex_acquire(ns_mutex_t *m, int th_id) {
    if(m->turn == th_id) {
        sem_wait(&m->lock);
        m->turn = (m->turn+1) % MAX_THREAD;
        sem_post(&m->s);
    }
    else {
        sem_wait(&m->s);
    }
}

void ns_mutex_release(ns_mutex_t *m) {
    sem_post(&m->lock);
    sem_post(&m->s);
}


void *worker(void *arg) {
    int i;
    int thread_id = *((int *) arg);
    for(i=0;i<loop;i++) {
        //sleep(1);
        ns_mutex_acquire(&nsmutex, thread_id);
        printf("I am thread: %i\n", thread_id);
        //sleep(1);
        ns_mutex_release(&nsmutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    pthread_t child[MAX_THREAD];
    int thread_id[MAX_THREAD];
    time_t now;
    struct tm *local_time;
    int i, rc;

    
    now = time(NULL);
    local_time = localtime(&now);
    printf("parent begin: %s\n", asctime(local_time));

    ns_mutex_init(&nsmutex);
    for(i=0;i<MAX_THREAD;i++) {
        thread_id[i] = i;
        rc = pthread_create(&child[i], NULL, worker, (void *) &thread_id[i]); assert(rc==0);
    }

    for(i=0;i<MAX_THREAD;i++) {
        rc = pthread_join(child[i], NULL); assert(rc==0);
    }

    printf("parent: end\n");
    return 0;
}

