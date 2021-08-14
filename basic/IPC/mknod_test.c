#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char filename[BUFFER_SIZE];
    int mkstatus;

    // if no argument is passed display usage
    if (argc <= 1) {
        printf("Usage: binary <device-path>\n");
        exit(0);
    }

    // copy argv[1] string to filename
    strcpy(filename, argv[1]);
    printf("Path: %s\n", filename);
   
   // create Named pipe FIFO using mknod
   if ((mkstatus = mknod(filename, S_IFIFO|0600, 0)) == -1) {
       printf("Error in making S_IFIFO\n");
       // If filename already exists, or is a symbolic link, this call fails with an EEXIST error.
       if(EEXIST) {
           printf("file: %s already exists\n", filename);
       }
       else {
           printf("Error in making Nmaed pipe\n");
       }
   }

   while (1) {
       if((fp = fopen(filename, "r")) == NULL) {
           printf("Error in opening S_IFIFO\n");
       }
       while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
           puts(buffer);
       }
       fclose(fp);
   }
}