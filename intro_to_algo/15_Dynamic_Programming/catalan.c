/*
   Author: Kumar Shubham

   Catalan number
*/


#include <stdio.h>
#include <stdlib.h>


void catalan(int *c, int n) {
    int i, j;
    for(i=1;i<=n;i++){
        c[i] = 0;
        for(j=0;j<i;j++){
            c[i] += c[j] * c[i-j-1];
        }
    }
}

int main(int argc, char *argv[]) {
    int n, i;
    printf("Enter n: ");
    scanf("%i", &n);
    printf("%i\n", n);

    int c[n+1];
    c[0] = 1;
    catalan(c, n);
    for(i=0;i<=n;i++){
        printf("%i%c", c[i], (i<n)?' ':'\n');
    }

    return 0;
}


