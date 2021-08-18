#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void spin(){
    int *p = malloc(sizeof(int));
    *p = 0;
    printf("Adderss of pointer: %p\n", p);
    while(1) {
        printf("pid: %i, count: %i\n", getpid(), (*p)++);
        sleep(1);
    }
}

int main(int argc, char *argv[]) {
    spin();
}