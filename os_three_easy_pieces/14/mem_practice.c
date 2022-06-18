#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    if( argc <2) {
        fputs("error\n", stdout);
        exit(-1);
    }

    int MAX_COUNT;
    MAX_COUNT = atoi(*(argv+1));
    int *x = (int *) malloc(MAX_COUNT * sizeof(int));
    printf("Address of x -> %p\n", x);

    int count = 0;
    while( count < MAX_COUNT){
        *(x+count) = count+10;
        count += 1;
    }

    count = 0;
    printf("after value:\n");
    while(count < MAX_COUNT){
        printf("%i\n", *(x+count));
        count +=1;
    }

    // reallocate 
    x = realloc(x, (MAX_COUNT+1) * sizeof(int));
    printf("reallocated Address of x -> %p\n", x);


    int *data = malloc(100);
    *(data+100) = 20;
    fprintf(stdout, "data[100]: %i\n", *(data+100));

    // try without free, then  valgrind <bin>
    // valgrind shoud report about
    free(data);
    free(x);

    // try to access after freeing up the memory
    fprintf(stdout, "%i\n", *(data));
}