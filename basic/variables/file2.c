#include <stdio.h>

extern int a;    // get 'a' from file1.c

void foo() {
    printf("%s a value:  %i\n", __FILE__, a);
}