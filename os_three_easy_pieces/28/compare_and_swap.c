/*
Author: Kumar Shubham

compare and swap lock

*/

#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<assert.h>
#include<pthread.h>
#include<sys/syscall.h>

typedef struct __lock_t {
    int flag;
}lock_t;

lock_t lock;
static volatile int count = 0;


int compareAndSwap(int *old_ptr, int expected, int new) {
    int actual = *old_ptr;

    if(actual == expected) {
        *old_ptr = new;
    }

    return actual;
}

void init_lock(lock_t *lock) {
    lock->flag = 0;
}

void my_lock(lock_t *lock) {
    while(compareAndSwap(&lock->flag, 0, 1) == 1) {
        printf("I am going to sleep: %lu\n", syscall(SYS_gettid));
        sleep(1);
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
        /* sleep shows here that compare and swap does not play fair, if thread A runs,
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
