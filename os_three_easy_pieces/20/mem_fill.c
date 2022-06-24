/*

# Author: Kumar Shubham
This program will consume the memory specified in MB

*/

#include <stdio.h>
#include <stdlib.h>      // malloc, rand, srand
#include <time.h>        // time
#include <string.h>      // memset

int main(int argc, char * argv[]){

    if(argc < 2){
        printf("./bin <size_Mb>\n");
        exit(0);
    }
    unsigned long int size;
    unsigned long int i = 0;

    size = atol(*(argv+1));
    printf("Intput size: %li\n", size);
    unsigned long int size_bytes = size*1024*1024;
    unsigned long int *my_array = malloc(size_bytes);
    unsigned char *ptr = (unsigned char *) my_array;
    //unsigned long int *my_array_tmp = malloc((unsigned long int) size*1024*1024);
    unsigned long int jump = size*1024/8;
    unsigned long int range = size*1024*1024/8;
    printf("len of int array: %li\n", range);

    // using memset
    /*while(1) {
        memset(my_array, 0, (unsigned long int) size*1024*1024);
    }
    */
    // below code will not able to fill up the memory
    /*
    while(1){
        for(i=0;i<range;i++){
            my_array[i] = 0;
        }
       printf("done\n");
    }
    */

    // Below code will fill up the memory
    while (1) {
        ptr = (unsigned char *) my_array;
        for(i=0;i<size_bytes;i++){
           *ptr++ = '0';
        }
    }
    
    free(ptr);
    free(my_array);
    return 0;
}