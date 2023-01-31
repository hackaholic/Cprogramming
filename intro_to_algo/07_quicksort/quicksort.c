/*
   Author: Kumar Shubham

   quick sort practice
*/

#include <stdio.h>
#include <time.h>
#include <errno.h>


void display(int a[], int n) {
    int i;
    for(i=0;i<n;i++) {
        printf("%i ", *(a+i));
    }
    printf("\n");
}

void swap(int a[], int i, int j) {
    int temp;

    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
} 

int partition(int a[], int p, int r) {

    int i = p, j = p;
    int x = a[r];

    for(;j<r;j++) {
        if(a[j] <= x) {
            swap(a, i, j);
            i++;
        }
    }
    swap(a, i, r);
    return i;
}

void quicksort(int a[],  int p, int r) {
    int q;

    if(p < r) {
        q = partition(a, p, r);
        quicksort(a, p, q-1);
        quicksort(a, q+1, r);
    }
}

int main(int argc, char *argv[]) {

    //int arr[] = {2, 8, 7, 1, 3, 5, 6, 4};
    //int arr[] = {0,0,0,0,0};
    int arr[] = {8, 7, 6, 5, 4, 3, 2, 1};
    //int arr[] = {1,2,3,4,5,6,7,8};

    int n = sizeof(arr)/sizeof(arr[0]);

    quicksort(arr, 0, n-1);
    printf("Sorted array: \n");
    display(arr, n);
    return 0;
}