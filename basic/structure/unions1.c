#include <stdio.h>
#include <string.h>

typedef enum __data_type {
    INT_TYPE, 
    FLOAT_TYPE, 
    CHAR_TYPE
} data_type;


typedef union __data {
    int a;
    float b;
    char c[10];
} data;

int main() {

    data mydata;
    data_type type;

    printf("storing int\n");
    type = INT_TYPE;
    mydata.a = 10;

    if(type == INT_TYPE) {
        fprintf(stdout, "Retreving int value: %i\n", mydata.a);
    }

    printf("storing string\n");
    type = CHAR_TYPE;
    strcpy(mydata.c, "hello Shiro");

    if(type == CHAR_TYPE) {
        fprintf(stdout, "Retreving str value: %s\n", mydata.c);
    }
    return 0;
}
