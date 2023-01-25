/*
   Author: Kumar Shubham
*/

#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {

    char a[100] = "Learning C is Fun. Learning pointer is more fun.\n";
    char *token = NULL;
    const char del[2] = " ";
    printf("%s\n", a);
    // On the first call to strtok(), the string to be parsed should be specified in str.
    token = strtok(a, del);
    while(token != NULL) {
        printf("%s\n", token);
        // In each subsequent call that should parse the same string, str must be NULL.
        // If a delimiter byte is found, it is overwritten with a null byte to terminate the current token.
        token = strtok(NULL, del);
    }

    printf("%s\n", a);
    return 0;
}