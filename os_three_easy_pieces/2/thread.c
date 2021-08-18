/*
   Author: Kumar Shubham
   compile: gcc -Wall -pthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int counter=0;
int loops;

void worker(int *arg) {
    for(int i=0;i<loops;i++) {
        counter++;
    }
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: binary <n>");
        exit(EXIT_FAILURE);
    }
    loops = atoi(argv[1]);
    pthread_t t1, t2;

    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Final Value: %i\n", counter);
}