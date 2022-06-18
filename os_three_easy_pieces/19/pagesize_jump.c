/*

# Author: Kumar Shubham
This program will detect TLB size and agerage time access a page

*/

#include <stdio.h>
#include <unistd.h>
#include <time.h>  // clock_gettime, timespec
#include <sys/time.h> // gettimeofday, timeval
#include <stdlib.h>   // malloc, calloc
#include <limits.h>


#define BILLION 1000000000L
#define MIN_TRY 1000

struct timespec tn_start, tn_end;

double total_timens(struct timespec t) {
    return  t.tv_sec  + (double) t.tv_nsec/BILLION;
}

void usage(){
    printf("./pagesize_jump <no_of_pages> <loop>\n");
    exit(0);
}

int main(int argc, char *argv[]){
    int jump = getpagesize()/sizeof(int);
    int i,j;
    int no_pages, n;
    double time_to_execute, avg_time_to_execute;

    // int getpagesize(void) -> return page size in int
    printf("PAGESIZE: %i\n", getpagesize());
    printf("sysconf(_SC_PAGESIZE): %i\n", _SC_PAGESIZE);
    printf("sysconf_SC_PAGE_SIZE): %lu\n", sysconf(_SC_PAGE_SIZE));

    if(argc < 2) {
        usage();
    }
    
    no_pages = atoi(argv[1]);
    n = atoi(argv[2]);
    if (n < 1000) {
        printf("n loop shoule be at least 1k\n");
        usage();
    }
    printf("no of pages: %i, loop: %i\n", no_pages, n);

    //int my_array[jump*no_pages];

    int *my_array = calloc(no_pages, getpagesize());

    clock_gettime(CLOCK_MONOTONIC, &tn_start);

    for(i=0; i<n;i++){
        //clock_gettime(CLOCK_REALTIME, &tn_start);
        for(j=0;j<=jump*no_pages;j+=jump){
            my_array[j] = 100;
        }
        //clock_gettime(CLOCK_REALTIME, &tn_end);
        //time_to_execute += total_timens(tn_end) - total_timens(tn_start);
    }
    
    printf("my_array[0]: %i\n", my_array[0]);
    clock_gettime(CLOCK_MONOTONIC, &tn_end);
    fprintf(stdout, "tn_end.tv_nsec: %li, tn_start.tv_nsec: %li\n", tn_end.tv_nsec, tn_start.tv_nsec);
    printf("nsec_diff: %li\n",  tn_end.tv_nsec - tn_start.tv_nsec);
    time_to_execute = total_timens(tn_end) - total_timens(tn_start);
    printf("total trails: %lu\n", (unsigned long int) n*no_pages);

    printf("time to execute above loop: %lf\n", time_to_execute);
    avg_time_to_execute = time_to_execute/(double)(n*no_pages);
    printf("Average time to access a page: %lf ns\n",  avg_time_to_execute*BILLION);

    free(my_array);
    return 0;


    /*
       tips :
       
       inside /proc
       meminfo
       vmstat
       vmacclocinfo
       cpuinfo
       pagetypeinfo

       inside /proc/<pid>
       maps
       smaps

       
    */
}