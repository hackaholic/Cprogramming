/*
   Author: Kumar Shubham
*/

#define max(a,b) (a>b)?a:b

#include <stdio.h>

// recursive approach
int cut_rod(int *p, int n) {
    int i,q;
    if(n == 0){
        return 0;
    }
    q = p[n];
    for(i=1;i<=n;i++) {
        q = max(q, p[i] + cut_rod(p, n-i));
    }
    return q;
}


// top down approach
int memoized_cut_rod(int *p, int *r, int n) {
    if(r[n]>=0){
        return r[n];
    }

    int q = p[n], i;
    for(i=1;i<=n;i++){
        q = max(q, p[i] + memoized_cut_rod(p, r, n-i));
    }
    r[n] = q;
    return q;
}

int bottom_up_memoized_cut_rod(int *p, int *r, int n) {
    if(n == 0 ){
        return r[n];
    }
    int q;
    int i,j;
    for(i=1;i<=n;i++) {
        q = p[i];
        for(j=1;j<=i;j++) {
            q = max(q, p[j] + r[i-j]);
        }
        r[i] = q;
    }

    return r[n];
}



int main(int argc, char *argv[]) {
    int p[] = {0, 1, 5, 8, 9, 10, 17, 20, 24, 30};
    int n = 4;
    int i;
    printf("max: %i\n", cut_rod(p, n));

    int r[n+1];
    r[0] = 0;
    for(i=1;i<=n;i++) {
        r[i] = -1;
    }
    printf("max: %i\n", memoized_cut_rod(p, r, n));

    r[0] = 0;
    for(i=1;i<=n;i++) {
        r[i] = -1;
    }
    printf("max: %i\n", bottom_up_memoized_cut_rod(p, r, n));

    return 0;
}