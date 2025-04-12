#include <stdio.h>

/*
An enum (short for enumeration) lets you assign names to a set of integer values. This makes code easier to read and manage.

enum Color { RED, GREEN, BLUE };
Compiler internally treats this as:
#define RED   0
#define GREEN 1
#define BLUE  2

*/


//By default, MON is 0, TUE is 1, and so on.
enum Day { MON, TUE, WED, THU, FRI, SAT, SUN };

// You can override values:
enum Status { SUCCESS = 1, FAILURE = 0, UNKNOWN = -1 };


typedef enum { RED, GREEN, BLUE } Color;

const char* COLORS[] = { "RED", "GREEN", "BLUE" };



// Assign custom values
typedef enum Permissions {
    READ = 1 << 0,   // 0001
    WRITE = 1 << 1,  // 0010
    EXEC = 1 << 2    // 0100
} Perm;


const char *colorToStr(const Color c)  {
    switch(c) {
        case RED:
            return "RED";
        
        case GREEN:
            return "Green";
        
        case BLUE:
            return "Blue";
        
        default: 
            return "Unknown";
    }

}

int main() {
    enum Day today = SAT;
    
    Color c = GREEN;

    if(today == SAT) {
        fprintf(stdout, "Today is Saturday\n");
    }

    printf("size of enum Day %lu\n", sizeof(enum Day));


    // looping over enum

    for(int i=RED; i<=BLUE;i++){
        printf("Color is %s\n", colorToStr(i));
        // also can access colors using array index, COLORS[i]
    }

    return 0;

}