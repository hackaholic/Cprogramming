#include <stdio.h>
#include <stdlib.h>

int MAX_COUNT = 10;
int main(int argc, char *argv[]){

    if( argc <2) {
        fputs("error\n", stdout);
    }
    int *x = (int *) malloc(MAX_COUNT * sizeof(int));
    printf("Address of x -> %p\n", x);

    int count = 0;
    while( count < MAX_COUNT){
        *(x+count) = count+10;
        count += 1;
    }

    count = 0;
    printf("after value:\n");
    while( count < MAX_COUNT){
        printf("%i\n", *(x+count));
        count +=1;
    }


    // reallocate 

    x = realloc(x, (MAX_COUNT+1) * sizeof(int));
    printf("reallocated Address of x -> %p\n", x);
}