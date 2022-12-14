/*
 Author: Kumar Shubham

 this program show thread concurrency issue.

*/

#include<stdio.h>
#include<time.h>
#include<pthread.h>
#include<assert.h>

static volatile int count = 0;


void *worker(void* arg) {

    int i;

    for(i=0;i<1e7;i++)
        count++;
    printf("Thread: %s\n", (char *) arg);
    return NULL;
}


int main(int argc, char *argv[]){ 
    time_t now;
    struct tm *local_time;
    int rc;

    pthread_t t1, t2;

    now = time(NULL);
    local_time = localtime(&now);

    printf("Main Starts here\n");
    fprintf(stdout, "Date: %s", asctime(local_time));

    rc = pthread_create(&t1, NULL, worker, "A"); assert(rc==0);
    rc = pthread_create(&t2, NULL, worker, "B"); assert(rc==0);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("count value is %i\n", count);
    printf("Main Ends Here\n");
    return 0;
}

