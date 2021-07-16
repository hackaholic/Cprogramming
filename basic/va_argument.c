#include <stdio.h>
#include <stdarg.h>

int sum(int i, ...) {
    va_list ap;
    int total = 0;

    va_start(ap, i); // initilization ap to point 1st arg
    total += i;

    while (i) {
        i = va_arg(ap, int);
        total += i;
    }
    va_end(ap);
    return total;
}

int main() {
    printf("sum(1,2,3,4,5,6)\n");
    printf("%i\n", sum(1,2,3,4,5,6));
}