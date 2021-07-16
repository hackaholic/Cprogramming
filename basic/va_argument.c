#include <stdio.h>
#include <stdarg.h>

int sumInt(int i, ...) {
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



/*
char, sort int will be promoted to  int, float will be promoted to double.
Compalier warning when float is passed
va_argument.c:26:24: warning: ‘float’ is promoted to ‘double’ when passed through ‘...’
   26 |         i = va_arg(ap, float);
      |                        ^
*/
float sumFloat(double i, ...) {
    va_list ap;
    double total = 0.0;
    va_start(ap, i);
    total += i;
    while (i) {
        i = va_arg(ap, double);
        printf("%f\n", i);
        total += i;
    }
    return total;
}

int main() {
    printf("sumInt(1, 2, 3, 4, 5, 6) -> %i\n", sumInt(1, 2, 3, 4, 5, 6));

    printf("sumFloat(1.2, 3.4, 6.6, 9.9) -> %f\n", sumFloat(1.2, 3.4, 6.6, 9.9));
}