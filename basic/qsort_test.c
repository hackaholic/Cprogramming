/*
    Author: Kumar Shubham
    #include <stdlib.h>
    qsort(void *base, int nmem, size_t size, int (*comp_func)(const void *, const void *))
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void usage() {
    printf("<binary> st1 str2 str3 ....\n");
}


int str_comp(const void *p1, const void *p2) {
    //char **a = (const char **)p1;
    //char **b = (const char **)p2;
    //return strcmp(*a, *b);

    return strcmp(*(const char **)p1, *(const char **)p2);
}

int main(int argc, char *argv[]) {

    if(argc<2) {
        usage();
        exit(0);
    }

    int i;
    qsort(argv[1], argc -1, sizeof(char *), (int*) str_comp);

    for(i=1;i<argc;i++) {
        printf("%s%c", argv[i], (i<argc-1)? ' ':'\n');
    }

    return 0;
}


