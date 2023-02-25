/*
    Author: Kumar Shubham
    Given a set of non-negative integers, and a value sum, determine if there is a subset of the given set with sum equal to given sum. 
*/

#include <stdio.h>
#include <stdlib.h>


// using recurssion 
int findsubset(int *a, int n, int sum) {

    // return 1 when sum is 0
    if(sum == 0) {
        return 1;
    }

    if(sum < 0 || n == 0) {
        return 0;
    }

    // if element is greater then sum then ignore it
    if(a[n-1] > sum) {
        return findsubset(a, n-1, sum);
    }

    // include the element or exclude the element
    return findsubset(a, n-1, sum-a[n-1]) || findsubset(a, n-1, sum); 
}

int dp_findsubset(int *a, int n, int sum){
    int i,j,x,y;

    int t[sum+1][n];
    for(i=0;i<sum;i++) {
        t[0][i] = 1;
    }

    for(i=1;i<=sum;i++) {
        for(j=0;j<n;j++){
            // including the element;
            x = (i-a[j]>=0)?t[i-a[j]][j]:0;

            // excluding the element
            y = (j>=1)?t[i][j-1]:0;

            t[i][j] = x || y;
        }
    }

    return t[sum][n-1];

}


void get_all_combinations(int *a, int n, int sum, int *path, int index) {
    int i;
    if(sum == 0){
        for(i=0;i<index;i++){
            printf("%i ", path[i]);
        }
        printf("\n");
        return;
    }

    if(sum<0 || n==0){
        return;
    }

    if(a[0] > sum) {
        get_all_combinations(a, n-1, sum, path, index);
        return;
    }

    // include the element
    path[index] = a[n-1];
    get_all_combinations(a, n-1, sum-a[n-1], path, index+1);

    //exclude the element
    get_all_combinations(a, n-1, sum, path, index);

}

int main(int argc, char *argv[]) {

    int arr[] = {3, 34, 4, 12, 5, 2};
    int len = sizeof(arr)/sizeof(arr[0]);
    int sum = 9;
    if(findsubset(arr, len, sum)){
        printf("True\n");
    }
    else {
        printf("False\n");
    }

    if(dp_findsubset(arr, len, sum)){
        printf("True\n");
    }
    else {
        printf("False\n");
    }
    
    int path[len];
    get_all_combinations(arr, len, sum, path, 0);
    return 0;
}
