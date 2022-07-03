/*

gcc -g basic.c
gdb a.out
break <line|function_name>    put breakpint at line or at function

*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    int i = 10;
    int j = 20;

    j = j+1;

    printf("Ok: %i, %i\n", i, j);
    return 0;
}