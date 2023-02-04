/*
 Author: Kumar Shubham

 Fibonacii number using dynamic programming
*/

#include <stdio.h>

// using recursive method
unsigned long int fib(unsigned int n) {

    if(n == 0 || n == 1) {
        return n;
    }
    return fib(n-1) + fib(n-2);

}


// using dynamic programming 

unsigned long int  bottom_up_fib(unsigned long int *r, unsigned int n) {
    unsigned int i;
    if( n == 0 || n == 1) {
        return n;
    }

    for(i=2;i<=n;i++){
        r[i] = r[i-1] + r[i-2];
    }
    return r[n];
}


unsigned long int top_down_fib(unsigned long int *r, unsigned int n) {

    if(n == 0 || n == 1) {
        return n;
    }
    else if(r[n] > 0) {
        return r[n];
    }
    r[n] = top_down_fib(r, n-1) + top_down_fib(r, n-2);
    return r[n];
}

// optimize space , as fib only need last two term to get current term

unsigned long int  space_optimized_fib(unsigned long int a, unsigned long int b, unsigned int n) {
    unsigned long int res, i;
    if( n == 0 || n == 1) {
        return n;
    }

    for(i=2;i<=n;i++){
        res = a+b;
        a = b;
        b = res;
    }

    return res;
}


int main(int argc, char *argv[]) {
    unsigned int n, i;;
    printf("enter n: ");
    scanf("%i", &n);
    if(n<=30){

    printf("fib(%i) -> %lu\n", n, fib(n));
    }

    unsigned long int r[n+1];
    r[0] = 0;
    r[1] = 1;

    printf("bottom_up_fib(%i) -> %lu\n", n, bottom_up_fib(r, n)); 

    for(i=2;i<=n;i++) {
        r[i] = 0;
    }

    printf("top_down_fib(%i) -> %lu\n", n, top_down_fib(r, n)); 

    printf("space_optimized_fib(%i) -> %lu\n", n, space_optimized_fib(0, 1, n));
    return 0;
}