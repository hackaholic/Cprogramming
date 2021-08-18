#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define MAX_CHAR 10

void spin(char *str) {
    time_t now;
    while (1) {
        now = time(NULL);
        printf("%s: %s\n", str, asctime(gmtime(&now)));
        sleep(1);
    }
}

int main(int argc, char *argv[]) {
    char str[MAX_CHAR];
    if (argc < 1) {
        printf("Usage: binary <string>\n");
        exit(EXIT_FAILURE);
    }
    strcpy(str, argv[1]);
    spin(str);
}