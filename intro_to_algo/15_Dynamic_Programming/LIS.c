/*
  Author: Kumar Shubham

  Given an array arr[] of size N, the task is to find the length of the Longest Increasing Subsequence (LIS) i.e.,
   the longest possible subsequence in which the elements of the subsequence are sorted in increasing order.

Input: arr[] = {50, 3, 10, 7, 40, 80}
Output: 4
Explanation: The longest increasing subsequence is {3, 7, 40, 80}

*/


#include <stdio.h>
#include <string.h>


int lis(int *a, int n) {
    int t[n], i,j;

    for(i=0;i<n;i++){
        t[i] = 1;
    }

    for(i=1;i<n;i++) {
        for(j=0;j<i;j++) {
            // if we can extend the sequence and take best 
            if((a[i]>a[j]) && (t[i]< 1+t[j])) {
                t[i] = 1 + t[j];
            }
        }
    }

    int max = 0;
    for(i=0;i<n;i++){
        if(t[i] > max) {
            max = t[i];
        }
    }

    return max;

}
int main(int argc, char *argv[]) {
    int arr[] = {50, 3, 10, 7, 40, 80};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Longest incresing sequence %i\n", lis(arr, n));
    return 0;
}

