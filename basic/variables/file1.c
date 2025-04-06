#include <stdio.h>

// Test Case 1: Normal Global Variable (a) , can be accessed by other files
// int a = 10;  

// Test case 2: Make a static in file1.c, other file cannot access it.
static int a; 

int main() {
    printf("%s a value:  %i\n", __FILE__, a);
    foo();
    return 0;
}


/*
static int a;
⇒ Defines a variable that has internal linkage
⇒ Only visible within the file it's defined in

extern int a;
⇒ Declares a variable that has external linkage
⇒ Defined in another file; you're just telling the compiler it exists

static void myFunction();
⇒ Defines a function with internal linkage
⇒ Only accessible within the file it's defined in
⇒ Cannot be used from another file even with 'extern'

void myFunction();
⇒ Defines a function with external linkage by default
⇒ Can be accessed from other files using 'extern'

extern void myFunction();
⇒ Declaration only — tells the compiler the function exists in another file
⇒ The actual definition should be in a different source file

*/

