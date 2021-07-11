#include <stdio.h>

// Macros Conditional Inclusion
#ifdef __STDC__
#    ifdef __STDC_VERSION__
#        define VERSION __STDC_VERSION__
#    endif
#endif

// max macros, Macros with arguments
#define max(a, b) (a > b) ? a : b

/* variadic macros that may have a variable number of arguments;
 these are mostly useful for dealing with variadic functions
*/
#define Warning(...) fprintf(stdout, "%s\n", ##__VA_ARGS__)

/*The comma operator evaluates both of its operands and 
returns the value of the one on the right-hand side. 
*/
#define NosyInc1(x) (printf("Incrementing %i by 1: ", x), (x)+1)
#define NosyInc2(x) (printf("Incrementing %i by 1: ", x), ++(x))

/* define macros printd use of #, 
A token passed to macro can be converted to a string literal by using # before it
*/
#define printd(expr) printf(#expr" -> %d\n", expr) 

#define aa1 "Hellow World"

//The tokens passed to macros can be concatenated using operator ## called Token-Pasting operator.
#define concat(front, back) front ## back

#define swap(T, x, y) { T tmp; tmp = x; x = y; y = tmp; } 

#define swap2(x, y) { typeof(x) tmp; tmp = x; x = y; y = tmp;}

int main() {
    int a = 2, b = 3;
    printf("Hello World\n");
    printf("Using Compiler Version: %li\n",  VERSION);
    printf("Current time: %s, Date: %s\n", __TIME__, __DATE__);
    
    printf("Max of a=%i, b=%i -> %i\n", a, b, max(a, b));
    printd(3/2);
    
    Warning("I am Learning", "Good Stuff");
    
    printf("%d\n", NosyInc1(5));  
    // Below Statement will producer error "lvalue required as increment operand"
    // printf("%d\n", NosyInc2(5)); 
    printf("%d\n", NosyInc2(b)); 

    printf("concat(123, 456) -> %i\n", concat(123, 456));
    printf("concat(aa, 1) -> %s\n", concat(aa, 1)); // this statement will produce error if aa1 is not defined
    
    // swap macro with type parameter
    swap(int, a, b);
    printf("After swap: a=%i, b=%i\n", a, b);
    //swap2 macro without type parameter
    swap2(a, b);
    printf("After swap2: a=%i, b=%i\n", a, b);
    return 0;
}