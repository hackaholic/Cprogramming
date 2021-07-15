#include <stdio.h>
#include <stdarg.h>



int main() {

    // formatting practice, printf returns number of character printed
    printf(":%s:\n", "Hello World");
    printf(":%30s:\n", "Hello World");
    printf(":%-30s:\n", "Hello World"); // Left alignment
    printf(":%.5s:\n", "Hello World");
    printf(":%20.5s:\n", "Hello World");

    char arr[20];
    // sprintf same as printf but stores the formatted output in string
    // sprintf(char *string, char *fmt, arg1, ag2,....)
    sprintf(arr, "Hello %s %s", "Coco", "Mini");
    printf("%s\n", arr);

    // scanf(char *fmt, ....) -> reads chracter from standard input
    // returns no of character read
    int i, n;
    printf("Enter an interger: ");
    n = scanf("%i", &i);
    if (n)
        printf("Ok\n");
    else 
       printf("Wrong input type\n");

    // sscanf(char *string, char *fmt, arg1, arg2, ...)
    // read character from input string
    char a[10], b[10], c[10];
    n = sscanf(arr, "%s %s %s", a, b, c);
    printf("%s %s %s\n", a, b ,c);
}