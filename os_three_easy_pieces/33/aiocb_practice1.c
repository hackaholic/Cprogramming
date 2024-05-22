/*
   gcc -Wall <prograname.c> -lrt
   The -lrt flag is used to link the real-time library (librt) when compiling a program. 
   This library contains various functions related to real-time programming, including functions for asynchronous I/O operations 
   (aio_read, aio_write, etc.). When you use these functions in your program, 
   you need to link against the real-time library to resolve the references to these functions.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <aio.h>

#include <assert.h>
#include <string.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    struct aiocb async_io;
    char buf[BUF_SIZE];

    char fileName[] = "hello_world.txt";
    int fd, rc;

    if((fd = open(fileName, O_RDONLY)) ==  -1) {
        perror("open():");
        exit(EXIT_FAILURE);
    }

    memset(&async_io, 0, sizeof(struct aiocb));
    async_io.aio_fildes = fd;
    async_io.aio_offset = 0;
    async_io.aio_buf = buf;
    async_io.aio_nbytes = BUF_SIZE;

    //read async
    rc = aio_read(&async_io);assert(rc==0);

    // wait for the read operation completes
    while(aio_error(&async_io) == EINPROGRESS);

    // get the return value when read operation completes
    rc = aio_return(&async_io);assert(rc > 0);

    buf[rc] = '\0';

    printf("Data read from file : %s\n %s\n", fileName, buf);

    close(fd);

    return 0;

}