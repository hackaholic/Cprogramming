#include <stdio.h>

int main() {
    char c;
    int i, arr[10];
    
    for (i=0;i<10;i++)
        arr[i] = 0;
    while ((c = getchar()) != EOF) {
        putchar(c);
        if (c >= '0' && c <= '9') {
            arr[c-'0']++;
        }
        if (c == '\n')
            break;
    }
    for (i=0;i<10;i++) {
        printf("%i -> %i\n", i, arr[i]);
    }
}