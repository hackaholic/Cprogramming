#include<stdio.h>
#include<stdlib.h>


int main(int argc, char *agrv[]) {

    const int a = 10;

    printf("const a: %i", a);

    // a = 20;
    // error: assignment of read-only variable 'a'
    // =,+=,-=, ++, -- are not allowed when keyworkd const is used

    //  hack using pointer, warning is displyed at compile time.
    int *p = &a;
    *p = 20;
    
    printf("const a: %i\n", a);

    return 0;
}