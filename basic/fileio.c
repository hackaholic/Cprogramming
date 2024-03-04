#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 10000



/*
    printf: Print formatted output to stdout.
    scanf: Read formatted input from stdin.
    getchar: Read a character from stdin.
    putchar: Write a character to stdout.
    getc: Read a character from a file.
    putc: Write a character to a file.
    sprintf: Write formatted data to a string.
    sscanf: Read formatted data from a string.
    fprintf: Write formatted data to a file.
    fscanf: Read formatted data from a file.
    fputs: Write a string to a file.
    fgets: Read a string from a file.
*/

void usage() {
    printf("Usage: ./binary.out <filename>\n");
    exit(0);
}

FILE *getfp(const char *filename) {
    // open file and return the FILE pointer
    FILE *fp;
    printf("Opening file %s\n", filename);
    fp = fopen(filename, "r");
    if (!fp) {
        printf("Error in opening file %s\n", filename);
        exit(1);
    } 
    return fp;
}

int main(int argc, char *argv[]) {
    printf("Weclome to I/O Practice\n");
    if (argc > 1)
        printf("Ok\n");
    else
        usage();
    
    // fopen(char *name, char *mode)
    char *filename = *++argv; 
    FILE *fp;
    fp = getfp(filename);
    // read character from he file
    int c;
    while ((c = getc(fp)) != EOF)
        putc(c, stdout);
    fclose(fp);

    // read line from file
    char line[MAX_CHAR];
    int max_line = 0;
    fp = getfp(filename);
    printf("ok\n");
    fprintf(stdout, "%s", line);
    while (fgets(line, MAX_CHAR, fp) != NULL) {
        max_line = (max_line > strlen(line)) ? max_line:strlen(line);
        fprintf(stdout, "%s", line);
    }

    printf("max line: %i\n", max_line);
    
}