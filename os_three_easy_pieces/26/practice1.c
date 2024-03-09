/*
Author: Kumar Shubham

A simple pthread example that creates multiple threads. 
Each thread will print a message indicating its ID and then exit. 
This will help us understand the basics of creating and managing pthreads.
*/

#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

#define MAX_THREAD 5

void *worker(void *t) {
    int val = (intptr_t)t;
    printf("I am thread %i, with ID: %ld\n",  val, syscall(SYS_gettid));
    sleep(1);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_t thread[MAX_THREAD];

    int i, rc;

    for(i=0;i<MAX_THREAD;i++) {
        rc = pthread_create(&thread[i], NULL, worker, (void *)(intptr_t)i);
        assert(rc ==0);
        write(STDOUT_FILENO, "thread created\n", 16);
    }

    for(i=0;i<MAX_THREAD;i++) {
        pthread_join(thread[i], NULL);
    }

    return 0;
}


/*
intptr_t is a signed integer type defined in the stdint.h header. 
It is guaranteed to be capable of holding a pointer to any object. 
The size of intptr_t is implementation-defined and is usually the same as the size of a pointer on the target platform.

Using intptr_t is useful when you need to convert between pointers and integers without loss of information or 
when you want to ensure that a pointer can be safely converted to an integer type. It's commonly used in scenarios where you need to 
store a pointer in an integer variable or pass a pointer as an integer argument to a function.


Here's the thing: on some platforms, int is the right size, but on others, long is the right size. 
How do you know which one is the one you should use? You don't. One might be right, 
but the standard makes no guarantees about which one it would be (if it is either). So the standard provides a type that is defined 
to be the correct size, regardless of what platform you're on.


*/