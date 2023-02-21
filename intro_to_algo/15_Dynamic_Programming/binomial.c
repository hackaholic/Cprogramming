/*
    Author: Kumar Shubham

    Binomial coefficient
    C(n,r) = C(n-1, r-1) + C(n-1, r)
    C(n,n) = C(n, 0) = 1
    where r <= n
*/


#include <stdio.h>
#include <stdlib.h>

int r_binomial(int n, int r) {
    if(n == r || r == 0){
        return 1;
    }

    return r_binomial(n-1, r-1) + r_binomial(n-1, r);
}



void dp_binomial(int n, int r) {
    int c[n+1][r+1];
    int i, j;
    
    for(i=1;i<=n;i++){
        for(j=0;j<=i && j<=r;j++){
            if(j == 0 || i==j){
                c[i][j] = 1;
            }
            else {
                c[i][j] = c[i-1][j-1] + c[i-1][j];
            }
        }
    }

    printf("dp_binomical: %i\n", c[n][r]);
}

int main(int argc, char *argv[]) {
    int r, n;

    printf("Enter value of n and r: ");
    scanf("%i %i", &n, &r);

    if(r > n) {
        printf("invalid input\n");
        exit(1);
    }

    printf("%i %i\n", n, r);

    printf("%iC%i: %i\n", n, r, r_binomial(n, r));

    dp_binomial(n, r);
    return 0;
}
