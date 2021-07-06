#include<stdio.h>

// symbolic constant
#define IN 1   
#define OUT 0

int main(){
    char c;
    int n = 0, nl = 0, ws = 0, wc = 0;
    int state = OUT;
    
    while ((c = getchar()) != EOF) { 
        putchar(c);
        printf("->%i, ", c);
        ++n;
        if ( c == '\n' )
          ++nl;
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state)
                ++wc;
            state = OUT;
            if (c == ' ')
                ++ws;
            else if (c == '\t')
                ws += 4;
        }
        else
            state = IN; 
    }
    printf("Total number of characters: %i\n", n);
    printf("Total number of words: %i\n", wc);
    printf("Total number of spaces : %i\n", ws);
    printf("Total number of lines: %i\n", nl);
}