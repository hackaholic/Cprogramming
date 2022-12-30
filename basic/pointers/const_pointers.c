#include<stdio.h>
#include<stdlib.h>


int main(int argc, char *agrv[]) {

    const int a = 10;
    const int b = 50;

    printf("const a: %i\n", a);

    // a = 20;
    // error: assignment of read-only variable 'a'
    // =,+=,-=, ++, -- are not allowed when keyword const is used

    //  hack using pointer, warning is displyed at compile time.
    // Read the pointer declarations right-to-left.
    int *p1 = &a;     // p1 is a pointer to integer
    *p1 = 20;
    
    printf("const a: %i\n", a);

    
    const int *p2 = &a;
    // read as -> p2 is a pointer to integer const
    //int const *p2 = &a;   // p2 is a pointer to const integer
    // *p2 = b is not allowed but p2 = &b is allowed

    const int * const p3 = &a;     // p3 is a const pointer to integer const
    //int const * const p3 = &a;   // p3 is a const ponter to const integer


    
    return 0;
}