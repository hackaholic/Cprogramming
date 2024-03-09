/*
Author: Kumar Shubham
Evaluting lock using test and set

test and set lock provides mutual exclusion
mutual exclusion: yes
fairness: no, other thread starve
performance: bad, spin lock waste cpu cycles of other waiting thread.

*/

#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<assert.h>
#include <sys/syscall.h>


static volatile int count = 0;

typedef struct __lock_t {
    int flag;
}lock_t;

lock_t lock;

int testandset(int *old_ptr, int new) {
    int old = *old_ptr;
    *old_ptr = new;
    return old;
}

void init_lock(lock_t *lock) {
    lock->flag = 0;
}

void my_lock(lock_t *lock) {
    while(testandset(&lock->flag, 1) == 1) {
        printf("I am going to sleep: %lu\n", syscall(SYS_gettid));  // system call is used to retrieve the thread ID of the calling thread
        sleep(1);          // sleep for 1 sec
    }
}

void my_unlock(lock_t *lock) {
    lock->flag = 0;
}

void *worker(void *arg) {
    int i;
    printf("Thread: %s, tid: %lu\n", (char *) arg, syscall(SYS_gettid));
    my_lock(&lock);
    for(i=0;i<1e7;i++) {
        count++;
        /* sleep shows here that test and set does not play fair, if thread A runs,
           it will let starve thread B and vice versa.
           No fairness
        */

        //sleep(1);   
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
    printf("Main starts here: %i\n", getpid()); 
    printf("Date: %s", asctime(local_time));

    rc = pthread_create(&t1, NULL, worker, (char *) "A"); assert(rc==0);
    rc = pthread_create(&t2, NULL, worker, (char *) "B"); assert(rc==0);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Count: %i\n", count);
    printf("Main End here\n");
    return 0;
}