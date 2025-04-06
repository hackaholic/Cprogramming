#include <stdio.h>


static int a = 10;   

void counter() {
    static int count = 0;   // persit value between multiple function call
    count++;
    printf("counter: %i\n", count);
}

void test() {
    extern int a;
    printf("test: %i\n", a);
}


int main() {
    counter();
    counter();
    counter();

    test();
    return 0;

}