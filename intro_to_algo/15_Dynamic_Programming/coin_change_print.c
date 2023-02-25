/*
  Author: Kumar Shubham

  Given an integer array of coins[ ] of size N representing different types of currency and an integer sum, 
  The task is to find the number of ways to make sum by using different combinations from coins[].
  And also print all possible combinations.

  Note: Assume that you have an infinite supply of each type of coin. 
*/

#include <stdio.h>
#include <stdlib.h>


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
    
    printf("table:\n");
    for(i=0;i<=sum;i++){
        for(j=0;j<n;j++){
            printf("%i%c", t[i][j], (j != (n-1))?' ':'\n');
        }
    }

    return t[sum][n-1];
}

// print all possible combinations
void get_all_combinations(int *a, int n, int sum, int *path, int index) {
    int i;
    if (sum == 0) {
        for (i = 0; i < index; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
        return;
    }

    if (n == 0 || sum < 0) {
        return;
    }

    // include the coin
    path[index] = a[0];
    get_all_combinations(a, n, sum-a[0], path, index+1);

    // exclude the coin
    get_all_combinations(a+1, n-1, sum, path, index);
}


int main(int argc, char *argv[]) {

    int arr[] = {1,2,5,10,20};
    //int arr[] = {2, 5, 1, 10, 20};
    int sum = 10;
    int len = sizeof(arr)/sizeof(arr[0]);

    printf("%i\n", dp_2d_get_coin_change(arr, len, sum));

    int path[sum];
    printf("All combinations:\n");
    get_all_combinations(arr, len, sum, path, 0);

    return 0;

}