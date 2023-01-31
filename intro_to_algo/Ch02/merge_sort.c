/*
   Author: Kumar Shubham

   MergeSort practice
*/

#include <stdio.h>

void display(int *a, int n) {
    int i;
    for(i=0;i<n;i++) {
        printf("%i ", *(a+i));
    }
    printf("\n");
}

void merge(int *arr, int p, int q, int r) {
    int lt = q-p+1;
    int rt = r-q;

    int l_arr[lt], r_arr[rt];
    int i, j, k;

    for(i=0;i<lt;i++)
       l_arr[i] = *(arr+p+i);
    
    for(i=0;i<rt;i++)
       r_arr[i] = *(arr+q+1+i);
    
    k = p;
    i = 0;
    j = 0;

    while(i<lt && j<rt) {
        if(l_arr[i] <= r_arr[j])
            *(arr+k++) = l_arr[i++];
        else {
            *(arr+k++) = r_arr[j++];
        }
    }

    for(;i<lt;i++)
        *(arr+k++) = l_arr[i];

    for(;j<rt;j++)
        *(arr+k++) = r_arr[j];

}

void mergesort(int *arr, int p, int r) {
    int q;
    if(p < r) {
        q = (p+r)/2;
        mergesort(arr, p, q);
        mergesort(arr, q+1, r);
        merge(arr, p, q, r);
    }

}

int main(int argc, char *argv[]) {

    //int arr[] = {2, 8, 7, 1, 3, 5, 6, 4};
    int arr[] = {2, 1, 3, 1, 2};
    //int arr[] = {7, 5, 3, 2, 1};
    //int arr[] = {0,0,0,0,0};
    //int arr[] = {8, 7, 6, 5, 4, 3, 2, 1};
    //int arr[] = {1,2,3,4,5,6,7,8};

    int n = sizeof(arr)/sizeof(int);

    mergesort(arr, 0, n-1);
    display(arr, n);
    return 0;
}