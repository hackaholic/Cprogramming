/*
    Author: Kumar Shubham
    mmap practice:
    void *mmap(void *addr, size_t length, int prot, int flags,
                int fd, off_t offset); 

    Map the memory region as Anonymous  
*/ 

#include<stdio.h>
#include<stdlib.h>
#include<error.h>
#include<time.h>
#include<sys/mman.h>
#include<string.h>


int main(int argc, char *argv[]) {

    int *addr;
    int n = 10, i;
 
     // mapping memory region using flag MAP_ANONYMOUS
     // when MAP_ANONYMOUS is applied fd is ignored
    if((addr = mmap(NULL, n*sizeof(int), PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0) ) == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    printf("mmap address: %p\n", addr);

    for(i=0;i<n;i++) {
        *(addr+i) = i; 
    }

    printf("Values from memory region: \n");
    for(i=0;i<n;i++) {
        printf("%i\n", *(addr+i));
    }

    // free up the memory
    munmap(addr, n*sizeof(int));
    return 0;
}