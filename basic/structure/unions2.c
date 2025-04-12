#include <stdio.h>
#include <string.h>




typedef enum __data_type {
    INT_TYPE, 
    FLOAT_TYPE, 
    CHAR_TYPE
} data_type;


// union inside struct 
typedef struct __union_data
{
    data_type dt;
    union {
        int a;
        float b;
        char c[10];
    };  //  // anonymous union , the union is declared inline and anonymous inside the struct, the members (a, b, c) are promoted to the struct level.
} union_data;

int main() {

    union_data mydata;

    printf("storing int\n");
    mydata.dt = INT_TYPE;
    mydata.a = 10;

    if(mydata.dt == INT_TYPE) {
        fprintf(stdout, "Retreving int value: %i\n", mydata.a);
    }

    printf("storing string\n");
    mydata.dt = CHAR_TYPE;
    strcpy(mydata.c, "hello Shiro");

    if(mydata.dt == CHAR_TYPE) {
        fprintf(stdout, "Retreving str value: %s\n", mydata.c);
    }
    return 0;
}
