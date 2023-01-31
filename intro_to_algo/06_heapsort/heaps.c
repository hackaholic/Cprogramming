/*
  Author: Kumar Shubham

  Heap prACTICE
  1) BUILD heap from array
  2) MAX_HEAPIFY
  3) Display heap
  4) heap sort

*/


#include<stdio.h>
#include<time.h>
#include<errno.h>
#include<stdlib.h>

void swap(int a[], int i, int j) {
    int temp;

    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void display_heap(int a[], int size) {
    int i;
    for(i=0;i<size;i++)
        printf("%i ", a[i]);
    printf("\n");

}

void max_heapify(int a[], int i, int size) {

    int largest;
    int l = (i<<1) + 1;
    int r =  l + 1;

    if(l<=size && a[l] > a[i])
        largest = l;
    else
        largest = i;
    
    if(r<=size && a[r]> a[largest])
        largest = r;

    if(i != largest){
        swap(a, i, largest);
        max_heapify(a, largest, size);
    }
}

void build_heap(int a[], int size) {
    int i = size/2;

    for(;i>=0;i--)
        max_heapify(a, i, size);
}

void heap_sort(int a[], int size) {
    while(size>0) {
       swap(a, 0, size--);
       max_heapify(a, 0, size);
    }

}

int main() {

    time_t now;
    struct tm *local_time;

    int arr[] = {1, 4, 7, 8, 2, 12, 20, 13, 99, 34};
    //int arr[] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
    int len = sizeof(arr)/sizeof(arr[0]);
    
    now = time(NULL);
    local_time = localtime(&now);

    printf("Main starts here: %s", asctime(local_time));
    printf("Array:\n");
    display_heap(arr, len);

    build_heap(arr, len-1);

    printf("Array after build heap:\n");
    display_heap(arr, len);

    heap_sort(arr, len-1);
    printf("Sorted array:\n");
    
    display_heap(arr, len);
    return 0;

}