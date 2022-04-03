/*
   Author: Kumar Shubham

*/

#include <stdio.h>
#include <time.h>

void get_time() {
    /*
    time_t time(time_t) -> This function returns the type time_t, time since 00:00:00 UTC, January 1, 1970 (Unix timestamp) in seconds.
    This function accepts single parameter second. This parameter is used to set the time_t object which store the time.
    time_t is long unsigned int 
    time(&time_t); to set time.

    */
    time_t now;
    now = time(NULL);
    printf("the time since 00:00:00 UTC, January 1, 1970, Unix timestamp: %ld\n", now);
}


// struct tm {
//    int tm_sec;         /* seconds,  range 0 to 59          */
//    int tm_min;         /* minutes, range 0 to 59           */
//    int tm_hour;        /* hours, range 0 to 23             */
//    int tm_mday;        /* day of the month, range 1 to 31  */
//    int tm_mon;         /* month, range 0 to 11             */
//    int tm_year;        /* The number of years since 1900   */
//    int tm_wday;        /* day of the week, range 0 to 6    */
//    int tm_yday;        /* day in the year, range 0 to 365  */
//    int tm_isdst;       /* daylight saving time             */
// };


void format_time(time_t t) {
    struct tm *time_gm, *time_local;

    // time_t now;
    // now = time(NULL);
    printf("Received timestamp: %ld\n", t);

    // struct tm *gmtime(const time_t *timep);
    // struct tm *localtime(const time_t *timep);
    // man localtime

    time_gm = gmtime(&t);
    printf("GM Date: %i-%i-%i %i:%i:%i\n", time_gm->tm_mday, time_gm->tm_mon+1, time_gm->tm_year+1900, time_gm->tm_hour, time_gm->tm_min, time_gm->tm_sec);
    
    // char *asctime(const struct tm *tm);
    // function converts the broken-down time value tm into a null-terminated string with the same format as ctime()
    printf("GM date using asctime: %s", asctime(time_gm));
    
    //time_t mktime(const struct *tm)
    printf("GM timestamp using mktime: %ld\n", mktime(time_gm));

    time_local = localtime(&t);
    printf("Local Date: %i-%i-%i %i:%i:%i\n", time_local->tm_mday, time_local->tm_mon+1, time_local->tm_year+1900, time_local->tm_hour, time_local->tm_min, time_local->tm_sec);
    printf("Local date using asctime: %s", asctime(time_local));
    printf("Local timestamp using mktime: %ld\n", mktime(time_local));

}

int main(int argc, char *argv[])
{
  time_t now;
  printf("Time/Clock Practice\n");
  get_time();
  format_time(time(NULL));
  return 0;
}