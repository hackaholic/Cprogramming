#include <stdio.h>

#define ALLOCSIZE 1000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

void *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp - n >= 0) {
        allocp += n;
        return allocp - n;
    }
    else
        return 0;   // Not enough space
}

void afree(char *p) {
    if (allocp >= allocbuf && allocp < allocbuf + ALLOCSIZE) {
        allocp = p;
    }
}