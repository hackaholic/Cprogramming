/*
   Author: Kumar Shubham

   Max priority Queue 

   1) heap_maximum              get max value of heap
   2) heap_extract_max          extract max value from heap
   3) heap_increase_key         replace with ne value
   4) max_heap_insert           insert a key into the heap
*/

#include<stdio.h>
#include<error.h>
#include<time.h>
#include<limits.h>

#define MAX_HEAP_SIZE 1000

void display(int a[], int size) {
    int i;
    for(i=0;i<size;i++)
        printf("%i ", a[i]);
    printf("\n");

}

void swap(int a[], int i, int j) {
    int temp;

    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void max_heapify(int a[], int i, int size) {
    int l = (i<<1) + 1;
    int r = l + 1;
    int largest = i;

    if(l<=size && a[l] > a[largest])
        largest = l;

    if(r<=size && a[r] > a[largest])
        largest = r;
    
    if( i != largest) {
        swap(a, i, largest);
        max_heapify(a, largest, size);
    }
}

void build_heap(int a[], int size) {
    int i = size/2;

    for(;i>=0;i--)
       max_heapify(a, i, size);
}

int get_heap_max(int a[]) {
    return a[0];
}

int pop_heap_max(int a[], int *size) {

    swap(a, 0, *size);
    *size -= 1;
    max_heapify(a, 0, *size);
    return a[*size+1];
}

int heap_increase_key(int a[], int index, int value, int size) {
    if(a[index] >= value) {
        printf("value %i is smaller then %i\n", value, a[index]);
        return 1;
    }

    a[index] = value;
    while(index >=0 && a[index/2] < a[index]){
        swap(a, index, index/2);
        index = index/2;
    }
    return 0;
}

void max_heap_insert(int a[], int value, int *size, int *len) {
    a[++(*size)] = INT_MIN;

    if(*len < *size)
        *len = *size + 1;
    
    heap_increase_key(a, *size, value, *size);

}

int main(int argc, char *argv[]) {

    time_t now;
    struct tm *local_time;
    int arr[MAX_HEAP_SIZE] = {1, 4, 7, 8, 2, 12, 20, 13, 99, 34};
    int len = 10;
    int heap_size = len-1;

    now = time(NULL);
    local_time = localtime(&now);
    printf("Main starts here: %s", asctime(local_time));   

    printf("Input arr:\n");
    display(arr, len);

    build_heap(arr, len-1);
    printf("Heap array:\n");
    display(arr, len);

    printf("value: %i\n", pop_heap_max(arr, &heap_size));
    display(arr, len);

    int index = 3, value = 63;
    heap_increase_key(arr, index, value, heap_size);
    printf("heap after increasing index %i to %i\n", index, value);
    display(arr, len);

    value = 9;
    max_heap_insert(arr, value, &heap_size, &len);
    printf("heap after inserting value %i\n", value);
    display(arr, len);
    return 0;
}

