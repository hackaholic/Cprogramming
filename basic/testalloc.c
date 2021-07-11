#include <stdio.h>


int main() {

    printf("Test of alloc.c\n");

    char *p = (char *) alloc(8 * sizeof(char));
    printf("returned address: %p\n", p);
}