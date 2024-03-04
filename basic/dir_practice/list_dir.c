#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <error.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

/*
   #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>

       int stat(const char *pathname, struct stat *statbuf);
       int fstat(int fd, struct stat *statbuf);
       int lstat(const char *pathname, struct stat *statbuf);

       for more info do  -> man 2 stat 
*/

int main(int argc, char *argv) {

    time_t t;
    struct tm *local_time;
    t = time(NULL);

    local_time = localtime(&t);
    printf("Current time %s\n", asctime(local_time));


    DIR *dp;   // pointer to dir
    struct dirent *entry;  // store entry
    struct stat stbuf;     //  struct for stat to store info about files
    
    if((dp = opendir(".")) == NULL) {
        perror(" Error While opening current dir");
        exit(EXIT_FAILURE);
    }
    
    while((entry = readdir(dp)) != NULL) {
        // skip 
        if(strcmp(entry->d_name, ".")  == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        
        stat(entry->d_name, &stbuf);
        fprintf(stdout, "Name -> %s %lu\n", entry->d_name, stbuf.st_size);
        
    }
    closedir(dp);
    return EXIT_SUCCESS;
}