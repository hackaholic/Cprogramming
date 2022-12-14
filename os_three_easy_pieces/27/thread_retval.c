/*

Author: Kumar Shubham

Thread practice to get return value.

*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<error.h>
#include<assert.h>

typedef struct __myarg_t {
    int a;
    int b;
}myarg_t;

typedef struct __myret_t {
    int x;
    int y;
}myret_t;

void *mythread(void *arg) {
    myarg_t *m = (myarg_t *) arg;
    printf("args: a: %i, b: %i\n", m->a, m->b);

    myret_t *r = (myret_t *) malloc(sizeof(myret_t));
    r->x = 1;
    r->y = 2;

    // return (void *) r;
    pthread_exit(r);
}

int main(int argc, char *argv[]) {
    time_t now;
    struct tm *local_time;
    pthread_t p;
    myarg_t args = {10,20};
    myret_t *m;
    int rc;
    now = time(NULL);
    local_time = localtime(&now);
    printf("Main starts here\n");
    printf("Date: %s", asctime(local_time));

    rc = pthread_create(&p, NULL, mythread, (void *) &args);assert(rc==0);
    rc = pthread_join(p, (void **) &m);assert(rc==0);

    printf("returned value: x: %i, y: %i\n", m->x, m->y);

    return 0;
}
