/*
    
    # Author: Kumar Shubham
    gcc -o access -fno-stack-protector -m32 -g
    
    gdb debug .....
    # set brek point using 
        break <*hex_address>|<func_name>|<line_number>
    # get all function
        info function
    
    # get assembly code of function
        disas <function_name>
    example: disas main

    get %esp register stack values
    x/nx $esp
    exmaple: x/20x 

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void granted() {
    printf("Access Granted\n");
}

int main(int argc, char *argv[]) {
    char buffer[10];
    int i;
    
    if(argc <2) {
        exit(1);
    }

    for(i=0;i<10;i++)
        buffer[i] = '\0';
    
    strcpy(buffer, *(argv+1));

    if(strcmp(buffer, "password") == 0)
        granted();
    else
        printf("Access denied\n");

    return 0;
}
