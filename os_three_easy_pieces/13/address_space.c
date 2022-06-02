#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    printf("Program start address :%p\n", (void *) main);
    int x;
    int y = 10;
    printf("address of initialized data %p\n", &y);
    printf("address of static bss: %p\n", &x);
    printf("address of HEAP: %p\n", (void *) malloc(1));
    return 0;
}