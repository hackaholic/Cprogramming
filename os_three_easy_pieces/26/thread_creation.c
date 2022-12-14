#include<stdio.h>
#include<pthread.h>
#include<assert.h>
#include<error.h>


void *my_thread(void *arg) {
    printf("thread: %s\n", (char *) arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;
    struct tm *local_time;
    time_t now;
    int rc;
    now = time(NULL);
    local_time = localtime(&now);

    printf("Starting Main\n");
    printf("Date time: %s", asctime(local_time));

    rc = pthread_create(&t1, NULL, my_thread, "A"); assert(rc==0);
    rc = pthread_create(&t2, NULL, my_thread, "B"); assert(rc==0);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Main Ends here\n");

    return 0;
}