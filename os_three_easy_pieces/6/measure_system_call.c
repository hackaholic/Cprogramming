/*
    Author: Kumar Shubham
    This Program measure the time taken by system call in microsec and nanosec.
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>

double total_timeus(struct timeval t) {
    return  t.tv_sec  + t.tv_usec * (1.0/1000000);
}

double total_timens(struct timespec t) {
    return  t.tv_sec  + t.tv_nsec * (1.0/1000000000);
}

void get_execution_timeus(long int loop, struct timeval *t) {
    long int i;

    // store start time
    gettimeofday(&t[0], 0);

    for(i=0;i<loop;i++) {
        time(NULL);
    }

    // store end time
    gettimeofday(&t[1], 0);

}

double get_execution_timens(long int loop, struct timespec *t) {
    long int i;
    struct timespec tmp;
 
    // man clock_gettime
    clock_gettime(CLOCK_REALTIME, &t[0]);

    for(i=0;i<loop;i++) {
        //time(NULL);
        clock_gettime(CLOCK_REALTIME, &tmp);
    }

    clock_gettime(CLOCK_REALTIME, &t[1]);
}

void usage() {
    printf("Usage: binary <loop> <u/n>\n");
    exit(EXIT_FAILURE);
}
int main(int argc, char *argv[]) {
    char choice;
    long int i, loop;
    double execute_time;
    struct timeval t_us[2];
    struct timespec t_ns[2];

    if(argc < 3) {
        usage();    
    }
    
    // no of time the to repeat system call 
    loop = atoi(argv[1]);
    choice = argv[2][0];

    switch(choice) {
        case 'u':
            get_execution_timeus(loop, t_us);
            execute_time = total_timeus(t_us[1]) - total_timeus(t_us[0]);
            printf("Total Time to execute: %lu sec\n", t_us[1].tv_sec - t_us[0].tv_sec);
            printf("Total Time to execute: %f usec\n", execute_time);
            break;
        case 'n':
            get_execution_timens(loop, t_ns);
            execute_time = total_timens(t_ns[1]) - total_timens(t_ns[0]);
            printf("Total Time to execute: %lu sec\n", t_ns[1].tv_sec - t_ns[0].tv_sec);
            printf("Total Time to execute: %f nsec\n", execute_time);
            break;
        default:
            usage();
            
    }

}