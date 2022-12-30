/*

Author: Kumar Shubham

producer consumer program using condition variable

*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<assert.h>
#include<error.h>
#include<sys/syscall.h>


#define MAX 5

int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;
int loops = 10;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;


int get() {
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % MAX;
    count--;
    return tmp;
}

void put(int val) {
    buffer[fill_ptr] = val;
    fill_ptr = (fill_ptr + 1) % MAX;
    count++;
}

void *producer(void *arg) {
    int i = 0;
    for(i=0;i<loops;i++) {
        pthread_mutex_lock(&lock);
        while(count == MAX)
            pthread_cond_wait(&empty, &lock);
        
        printf("produer: loop: %i, put val: %i\n", i, i*10);
        put(i*10);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {

    int i = 0;
    for(i=0;i<loops;i++){
        pthread_mutex_lock(&lock);
        while(count == 0)
            pthread_cond_wait(&fill, &lock);
        
        int val = get();
        printf("Consumer: loop: %i, val: %i\n", i, val);
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {

    time_t now;
    struct tm *local_time;
    pthread_t t1, t2;
    int rc;

    now = time(NULL);
    local_time = localtime(&now);

    printf("Main starts here: %s", asctime(local_time));

    rc = pthread_create(&t1, NULL, producer, NULL);assert(rc==0);
    rc = pthread_create(&t2, NULL, consumer, NULL);assert(rc==0);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main End...\n");

    return 0;

}
