#include <stdio.h>

int main(){
    char c;

    printf("Provide some text\n");
    c = getchar();    // getchar can only read stream from standard input
    while (c != EOF) {  // read will fail when encounter EOF
        putchar(c);
        c = getchar();
    }

    // CTRL-D will send EOF to stdin

    /*
     int feof (FILE *stream)
     Tests for end-of-file on a stream. 
    */

    if (feof(stdin)) {              
        printf("Gotcha EOF\n");
    }
    printf("\n");
    printf("EOF is: %i\n", EOF);
}