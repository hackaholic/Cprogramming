/*
  Author: Kumar Shubham

  Open file and map to region, modifiy the region and write back to file.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

#define MAX_BUF 100

int main(int argc, char *argv[]) {

    char *addr;
    const char *filename = "hello.txt";
    int fd;

    const char *text = "Hello World, Coco is a lovely Cat";

    if((fd = open(filename, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR)) == -1) { 
        perror("open");
        exit(EXIT_FAILURE);
    } 
    
    lseek(fd, strlen(text)-1, SEEK_SET);
    write(fd, "", 1);

    // load the file to memory region
    if((addr = mmap(NULL, MAX_BUF, PROT_READ|PROT_WRITE, MAP_SHARED, fd,  0)) == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // modify the memory region
    memcpy(addr, text, strlen(text));
    // dump the content of memory to file
    msync(addr, strlen(text),  MS_SYNC);

    munmap(addr, MAX_BUF);
    close(fd);
    return 0;
}