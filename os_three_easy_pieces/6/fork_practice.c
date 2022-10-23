#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>        // sleep
#include<sys/wait.h>

#define RANGE 10
#define MAX_PROCESS 5

void go_sleep(int n) {
    fprintf(stdout, "Sleeping for %d sec\n", n);
    sleep(n);
}

int get_random_n() {
    // struct timespec tn;
    // clock_gettime(&tn);
    // srand(tn.tv_sec  + tn.tv_nsec * (1.0/1000000));
    int my_rand = rand() % RANGE;
    // printf("RAND_MAX:%lu\n", RAND_MAX);
    printf("get_random_n random: %i\n", my_rand);
    return my_rand;
}

int main() {
    pid_t jobs_id[MAX_PROCESS];
    int i,n;
    int wstatus;
    for(i=0;i<MAX_PROCESS;i++){
        n = get_random_n();
        printf("%i----- %i\n", i, n);
        if((jobs_id[i] = fork()) == -1) {
            fprintf(stderr, "Error in Spawnning process\n");
        }
        else if(jobs_id[i] == 0) {
            printf("I am child: %i\n", getpid());
            //n = get_random_n();
            //printf("2----- %i\n", n);
            //go_sleep(n);
            go_sleep(get_random_n());
            exit(0);
        }
    }
    
    printf("Spawned processess:\n");
    for(i=0;i<MAX_PROCESS;i++) {
        printf("pid: %i\n", jobs_id[i]);
    }

    int j = MAX_PROCESS;
    pid_t child_pid;
    while(j > 0){
        child_pid = wait(&wstatus);
        printf("child: %i exited with status: %i\n", child_pid, wstatus);
        j--;
    }
    //go_sleep(my_rand);
    return 0;
}

