/*
  Author: Kumar Shubham
*/


#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {

    int **arr;
    int n = 3, c = 4;
    int i, j;

    // allocation size for the arr
    arr = malloc(n*sizeof(int *));
    for(i = 0; i<n; i++) {
        // need to allocated memory for each row
        *(arr +i) = malloc(c*sizeof(int));
    }

    // inserting value to 2D arr
    for(i=0;i<n;i++) {
        for(j=0;j<c;j++) {
            *(*(arr+i)+j) = (i+1)*(j+1);
        }
    }

    // Displaying value
    for(i=0;i<n;i++) {
        for(j=0;j<c;j++) {
            printf("%i%c", *(*(arr+i)+j), (j<c-1)?' ': '\n');
        }
    }


    // free the memory

    for(i=0;i<n;i++){
        free(*(arr+i));
    }

    free(arr);
    return 0;
}