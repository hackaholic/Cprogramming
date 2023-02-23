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
    
    return 0;
}
