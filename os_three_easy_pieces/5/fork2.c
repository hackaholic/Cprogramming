#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>


int main(int argc, char*argv[]) {
    int n = 3;
    for(int i=0;i<n;i++){
        fork();
    }
    printf("Hello: pid: %i\n", getpid());
    while(wait(NULL) !=-1)
        continue;
}