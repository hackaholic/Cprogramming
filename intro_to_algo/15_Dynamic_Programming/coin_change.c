/*
  Author: Kumar Shubham

  Given an integer array of coins[ ] of size N representing different types of currency and an integer sum, The task is to find the number of ways to make sum by using different combinations from coins[].  

  Note: Assume that you have an infinite supply of each type of coin. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_coin_change(int *a, int n, int sum) {
    if(sum == 0) {
        return 1;
    }

    if(sum < 0 || n == 0) {
        return 0;
    }

    return get_coin_change(a, n, sum-a[n-1]) + get_coin_change(a, n-1, sum);
}


// using dynamic programming 2D array (tabulation) 

int dp_coin_change(int *a, int n, int sum){
    int tab[n+1][sum+1];
    int i,j;
    memset(tab, 0, sizeof(tab[0][0])*(n+1)*(sum+1));
    tab[0][0] = 1;

    for(i=1;i<=n;i++) {
        for(j=0;j<=sum;j++) {
            // including the coin
            tab[i][j] += (j-a[i-1]>=0) ? tab[i][j - a[i-1]] : 0;

            // excluding the coin
            tab[i][j] += tab[i-1][j];
        }
    }

    return tab[n][sum];

}

int dp_2d_get_coin_change(int *a, int n, int sum) {
    int i,j;
    int x, y;
    int t[sum+1][n];

    // base case
    for(i=0;i<n;i++){
        t[0][i] = 1;
    }

    for(i=1;i<=sum;i++) {
        for(j=0;j<n;j++) {
            // including the coin
            x = ((i-a[j]) >= 0)?t[i-a[j]][j]:0;

            // excluding the coin
            y = (j>=1)?t[i][j-1]:0;
            t[i][j] = x+y;
        }
    }

    return t[sum][n-1];
}


// using Dynamic programming 1D array

int dp_1d_get_coin_change(int *a, int n, int sum) {

    int i, j;
    int t[sum+1];

    memset(t, 0, (sum+1)*sizeof(int));
    // base case
    t[0] = 1;

    for(i=0;i<n;i++) {
        for(j=a[i];j<=sum;j++){
            t[j] += t[j-a[i]];
        }
    }

    return t[sum];
}

int main(int argc, char *argv[]) {

    // int arr[]= {1, 2, 3};
    // int sum = 4;

    int arr[]= {2, 5, 3 ,6};
    int sum = 10;
    int len = sizeof(arr)/sizeof(arr[0]);

    printf("%i\n", get_coin_change(arr, len, sum));

    printf("%i\n", dp_2d_get_coin_change(arr, len, sum));

    printf("%i\n", dp_1d_get_coin_change(arr, len, sum));

    printf("%i\n", dp_coin_change(arr, len, sum));
    return 0;
    return 0;
}
