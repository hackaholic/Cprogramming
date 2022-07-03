/*
    Author: Kumar Shubham
    gcc -fno-stack-protector -m32 -g stackoverflow.c

    -m32 for 32 bit address space
    -fno-stack-protector ->  distable stack protection from executing code, base, bound, check etc.
    -g add addition info to the binary

    gdb a.out
    run $(python3 -c 'print("A"*10)')
    disas main
    info func

    break *<HEX_ADDRESS>

    x/20x $ esp  -> list esp 

*/


#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    char buffer[6];
    strcpy(buffer, argv[1]);
    printf("%s\n", buffer);
    return 0;
}