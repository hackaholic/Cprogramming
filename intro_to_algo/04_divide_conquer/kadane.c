/*
  Author: Kumar Shubham
  Maximum subarray using kadane algorithm.
*/

#include<stdio.h>
#include<limits.h>

void max_subarray(int a[], int len) {
    int i, s = 0, start, end;
    int sum = 0;
    int max_sum = INT_MIN;

    for(i=0;i<len;i++) {
        sum += a[i];
        if(sum >= max_sum) {
            max_sum = sum;
            end = i;
            start = s;
        }

        if(sum < 0) {
            sum = 0;
            s = i+1;
        }
    }

    printf("max subarray sum %i\n", max_sum);
    printf("Index: %i, %i\n", start, end);
}

int main(int argc, char *argv[]) {
    // int a[] = {-2, -5, 6, -2, -3, 1, 5, -6};
    int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};

    int len = sizeof(a)/sizeof(a[0]);

    max_subarray(a, len);

    return 0;
}