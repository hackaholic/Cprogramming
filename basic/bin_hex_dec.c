/*
     Author: Kumar Shubham


     error:

    # gcc bin_hex_dec.c
    /tmp/ccgRkYN0.o: In function `hex_dec':
    bin_hex_dec.c:(.text+0x136): undefined reference to `pow'
    collect2: error: ld returned 1 exit status
    one need to link math lib
    # gcc bin_hex_dec.c -lm -o bin_hex_dec 
*/

#include <stdio.h>
#include <stdlib.h>    //  exit
#include <string.h>    //  strcpy
#include <math.h>      //  pow
#include <ctype.h>     // tolower

#define MAX_LENGHT 100
#define HEX_BASE 16
#define DEC_BASE 10
#define BIN_BASE 2

void usage(){
    fprintf(stdout, "./bin_dec_hex <decimal|hexadecimal|binary>\n");
    exit(0);
}

int is_bin_dec_hex(char *p){
    int flag = 0;
    
    while(*p != '\0'){
        if( *p == '0' || *p == '1'){
            flag |= 1;
        }
        else if(*p >= '0' && *p <= '9'){
            flag |= 2;

        }
        else if( (*p >= 'a' && *p <= 'f') || ( *p >= 'A' && *p <= 'F') ){
            flag |= 4;
        }
        else{
            flag = 0;
            break;
        }
        p++;
    }
    return flag;
}

void hex_dec(char *hex){
    
    double dec =  0;
    char c;
    double pow_val;
    int count = 0;
    int len = strlen(hex)-1;

    while(len >= 0 ){
        c = tolower(*(hex+len));
        pow_val = pow(HEX_BASE, count);
        if( *(hex+len) <= '9')
        {
            dec += (c - '0') * pow_val;
        }
        else {
            dec += ((c - 'a') + DEC_BASE) * pow_val;
        }
        count++;
        len--;
    }

    printf("Decimal: %.0f\n", dec);

}

void dec_to4bit(int dec) {
    int rem;
    char bit[5] = {"0000\0"};
    int count = 0;
    //printf("dec: %i, %s\n", dec, bit);
    while (dec != 0){
        rem = dec % BIN_BASE;
        dec /= BIN_BASE;
        //printf("--- count %i\n", count);
        if(rem){
            bit[3-count] = '1';
        }
        else {
            bit[3-count] = '0';
        }
        //printf("rem: %i\n", rem);
        count++;
    }
    //bit[4] = '\0';
    printf("%s", bit);

}

void hex_bin(char *hex) {
    printf("Binary: ");
    while(*hex != '\0'){
        if (*hex >= '0' && *hex <= '9'){
            dec_to4bit(*hex - '0');
        }
        else {
            dec_to4bit((tolower(*hex) - 'a') + DEC_BASE);
        }
        hex++;
    }
    printf("\n");
}

void dec_hex(int dec){
    int rem;
    int count = 0;
    char hex[100];
    printf("Hexadecimal: ");
    while (dec != 0){
        rem = dec % HEX_BASE;
        dec /= HEX_BASE;
        //printf("--- count %i\n", count);
        if(rem >= 0 && rem < DEC_BASE){
            hex[count++] =  '0' + rem;
        }
        else{
            hex[count++] = 'A' + rem - DEC_BASE;
        }
    }
    hex[count] = '\0';

    while(count >= 0){
        putchar(hex[count--]);
    }
    printf("\n");
}

void dec_bin(int dec){
    int rem;
    int count = 0;
    char bin[100];
    printf("Binary: ");
    while (dec != 0){
        rem = dec % BIN_BASE;
        dec /= BIN_BASE;
        //printf("--- count %i\n", count);
        if(rem){
            bin[count++] =  '1';
        }
        else{
            bin[count++] = '0';
        }
    }
    bin[count] = '\0';

    while(count >= 0){
        putchar(bin[count--]);
    }
    printf("\n");
}

unsigned long int bin_dec(char *bin) {
    unsigned long int dec = 0;
    int len;
    len = strlen(bin)-1;
    while(*bin != '\0'){
        dec += (*bin++ - '0') * pow(BIN_BASE, len--);
    }
    return dec;
}

void bin_hex(char *bin){
    dec_hex(bin_dec(bin));
}

int main(int argc, char *argv[]){
    
    if( argc < 1 ){
        usage();
    }

    char *str;
    int flag;
    str = *(argv+1);
    printf("Input value: %s\n", str);
    flag = is_bin_dec_hex(str);
    switch(flag){
        case 4:
        case 5:
        case 6:
        case 7:
            printf("Hexadecimal number detected ...\n");
            hex_dec(str);
            hex_bin(str);
            //  dec_hex
            break;
        case 2:
        case 3:
            printf("Decimal number detected ...\n");
            dec_hex(atoi(str));
            dec_bin(atoi(str));
            break;
        case 1:
            printf("Binary Number detected ...\n");
            printf("Decimal: %lu\n", bin_dec(str));
            bin_hex(str);
            break;
        default:
            printf("invalid input :( \n");
            usage();
            break;
    }
    return 0;
}