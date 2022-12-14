/*
 Author: Kumar Shubham
 Thread lock practice, avoid race condition
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<assert.h>
#include<errno.h>
#include<time.h>


static volatile int count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *mythread(void *arg) {
    int i;
    for(i=0;i<1e7;i++) {
        pthread_mutex_lock(&lock);
        count++;
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;
    time_t now;
    struct tm *local_time;

    now = time(NULL);
    local_time = localtime(&now);
    printf("Main Starts here, count: %i\n", count);
    printf("Date: %s", asctime(local_time));

    if((pthread_create(&t1, NULL, mythread, NULL)) != 0) {
        printf("Error in creating thread t1\n");
        exit(EXIT_FAILURE);
    }

    if((pthread_create(&t2, NULL, mythread, NULL)) != 0) {
        printf("Error in creating thread t2\n");
        exit(EXIT_FAILURE);
    }
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Count: %i\n", count);
    return 0;
}
