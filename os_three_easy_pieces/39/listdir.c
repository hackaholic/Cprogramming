/*
    Author: Kumar Shubham

    List the content of the directory
*/


#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<time.h>
#include<string.h>


void listdir(char *dirname) {
    DIR *d;
    struct dirent *d_ent;

    d = opendir(dirname);
    while((d_ent = readdir(d)) != NULL) {
        printf("name: %s\n", d_ent->d_name);
        printf("inode no: %lu\n", (unsigned long) d_ent->d_ino);
        printf("offset: %ld\n", (long) d_ent->d_off);
        printf("record length: %i\n", d_ent->d_reclen);
        printf("type: %i\n", d_ent->d_type);
        printf("\n");   
    }

}

int main(int argc, char *argv[]) {
    char *dirname;

    if(argc < 2) {
        printf("Usage: binary <dir_path>\n");
        exit(0);
    }

    dirname = *(++argv);
    printf("Opening dir: %s\n", dirname);
    listdir(dirname);

    return 0;

}


