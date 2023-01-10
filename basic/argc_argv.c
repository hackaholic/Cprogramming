/*
    Author: Kumar Shubham

    Command line argc and argv practice


    
    argv  -> [8 byte address, 8 byte address, .....]
                   |               |
                   x               x
              [programename]    [ arg1 ]
*/


#include<stdio.h>

int main(int argc, char *argv[]) {
    
    // char *argv[] -> argv is an array of pointer to char

    int i;

    for(i=0;i<argc;i++) {
        printf("%p: %s\n", argv+i, *(argv+i));
    }
    return 0;
}