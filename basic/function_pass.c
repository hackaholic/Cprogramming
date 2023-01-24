/*
    Author:Kumar Shubham

    Fass function 

    prototype:

    void function(int p1, int p2, <type> (*func)(<type>, <type>))
    void function(int p1, int p2, <type> (*func)(<type>, <type>))

*/


#include <stdio.h>



int sum(int n) {

    int i = 0, sum = 0;

    for(i=0;i<n;i++){
        sum += i;
    }

    return sum;

}


int test(int n, int func(int)) {

    return func(n);
}

int main(int argc, char *argv[]) {

    int n = 5;

    int s = test(n, sum);

    printf("%i\n", s);

    return 0;
}