#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {

    int x;
    int y = 0;
    char *z = malloc(1);

    printf("my pid: %i\n", getpid());
    printf("%p : main\n", &main);
    printf("%p : main\n", (void *) main);
    printf("%p : uninitialized data\n", &x);
    printf("%p : initialized data\n", &y);
    printf("%p : heap\n", z);
    while(1){
        sleep(1);
    }
    return 0;
}