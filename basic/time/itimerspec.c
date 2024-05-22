/*
Author: Kumar Shubham

   #include <time.h>

       struct itimerspec {
           struct timespec  it_interval;   // Interval for periodic timer 
           struct timespec  it_value;     // Initial expiration 
       };
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

void timer_handler(int signum) {
    printf("Timer expired\n");
}

int main(int argc, char *argv[]){
    timer_t timerid;
    struct itimerspec its;

    int rc;


    /*
     timer_create and timer_settime functions, when a timer created with these functions expires, 
     it generates a signal. By default, this signal is SIGALRM, but you can specify a different 
     signal when creating the timer using the struct sigevent and timer_create functions
    */
    signal(SIGALRM, timer_handler);

    // create timer
    if((rc = timer_create(CLOCK_REALTIME, NULL, &timerid)) == -1) {
        perror("Error: timer_create() ");

    }

    its.it_value.tv_sec = 2;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;

    // arm the timer
    if((rc = timer_settime(timerid, 0, &its, NULL)) == -1) {
        perror("Error: timer_settime()");
        exit(EXIT_FAILURE);
    }

    /*
    pause() causes the calling process (or thread) to sleep until a signal is delivered that either terminates
       the process or causes the invocation of a signal-catching function.
    pause() returns only when a signal was caught and the signal-catching function returned.   In  this  case,
       pause() returns -1, and errno is set to EINTR

    more on -> man pause   

    */
    pause();

    return 0;


}
