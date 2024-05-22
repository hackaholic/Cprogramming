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
    char buf[BUF_SIZE] = "Hello, Async IO!";
    char fileName[] = "output.txt";
    int fd, rc;

    if ((fd = open(fileName, O_CREAT | O_WRONLY | O_TRUNC, 0664)) == -1) {
        perror("open():");
        exit(EXIT_FAILURE);
    }

    memset(&async_io, 0, sizeof(struct aiocb));
    async_io.aio_fildes = fd;
    async_io.aio_offset = 0;
    async_io.aio_buf = buf;
    async_io.aio_nbytes = strlen(buf);

    // Write asynchronously
    rc = aio_write(&async_io);
    assert(rc == 0);

    // Wait for the write operation to complete
    while (aio_error(&async_io) == EINPROGRESS);

    // Get the return value when write operation completes
    rc = aio_return(&async_io);
    assert(rc == strlen(buf));

    printf("Data written to file : %s\n", fileName);

    close(fd);

    return 0;
}
