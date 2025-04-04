# include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Global initialized variable (Stored in Initialized Data Segment)
int global_init = 10;

// Global uninitialized variable (Stored in BSS -  Block Started by Symbol)
int global_uninit;

void function() {
    // Local variable (Stored in Stack)
    int local_var = 20;
    
    // Dynamically allocated memory (Stored in Heap)
    int *heap_var = (int *)malloc(sizeof(int));
    *heap_var = 30;

    printf("Local Variable (Stack): %d\n", local_var);
    printf("Heap Variable (Heap): %d\n", *heap_var);
    printf("sleeping so you can debug pmap\n");
    sleep(600);
    free(heap_var); // Free allocated memory
}

int main(int argc, char *argv[]) {

    char *str = "Hello Coco\n";  // stored in read only section

    printf("process id: %d\n", getpid());
    printf("Global Initialized (Data): %d\n", global_init);
    printf("Global Uninitialized (BSS): %d\n", global_uninit);
    printf("String Literal (Read-Only Data): %s\n", str);

    function(); // Call function to use stack and heap

    return 0;

}