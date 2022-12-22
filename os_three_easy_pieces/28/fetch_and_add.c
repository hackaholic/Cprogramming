/*
Author: Kumar Shubham

Fetch and add Lock
mutual Exclusion: yes
fairness: Yes
Performance: Bad, cpu cycle get wasted in spin, when thread are waiting for their turn.

*/


#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<assert.h>
#include<time.h>
#include<sys/syscall.h>

typedef struct __lock_t {
    int ticket;
    int turn;
}lock_t;

lock_t lock;
static volatile int count = 0;

int fetchAndAdd(int *old_ptr) {
    int old = *old_ptr;
    *old_ptr = old + 1;
    return old;
}


void lock_init(lock_t *lock) {
    lock->ticket = 0;
    lock->turn = 0;
}

void my_lock(lock_t *lock) {
    int turn = fetchAndAdd(&lock->ticket);
    while(turn != lock->turn) {
        printf("I am going to sleep: %lu\n", syscall(SYS_gettid));
        sleep(1);
    }
}

void my_unlock(lock_t *lock) {
    lock->turn += 1;
}

void *worker(void *arg) {
    int i;
    printf("Thread: %s, tid: %lu\n", (char *) arg, syscall(SYS_gettid));
    my_lock(&lock);
    for(i=0;i<1e7;i++){
        count++;
         // sleep(1)
    }
    my_unlock(&lock);
    return NULL;
}

int main(int argc, char *argv[]) {
    time_t now;
    struct tm *local_time;
    pthread_t t1, t2;
    int rc;

    now = time(NULL);
    local_time = localtime(&now);
    printf("Main starts here\nDate: %s", asctime(local_time));

    lock_init(&lock);
    rc = pthread_create(&t1, NULL, worker, (char *) "A"); assert(rc==0);
    rc = pthread_create(&t2, NULL, worker, (char *) "B"); assert(rc==0);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Count: %i\n", count);
    printf("Main End here\n");

    return 0;

}


