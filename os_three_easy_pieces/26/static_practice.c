/*
static keyword in c


    Static global variable
    When a global variable is declared with a static keyword, then it is known as a static global variable. It is declared at the top of the program, and its visibility is throughout the program.
    
    Static function
    When a function is declared with a static keyword known as a static function. Its lifetime is throughout the program.
    
    Static local variable
    When a local variable is declared with a static keyword, then it is known as a static local variable. The memory of a static local variable is valid throughout the program,
     but the scope of visibility of a variable is the same as the automatic local variables. However, when the function modifies the static local variable during the first function call, then this modified value will be available for the next function call also.
    if not initialized by default it will initialized as 0

    Static member variables
    When the member variables are declared with a static keyword in a class, then it is known as static member variables. They can be accessed by all the instances of a class, not with a specific instance.
    
    Static method
    The member function of a class declared with a static keyword is known as a static method. It is accessible by all the instances of a class, not with a specific instance.

*/

/*
  
  const: when a variable is decleared with const it cannot be reassigned
  const int a = 10;

  a =20  ;   # compile error
*/



#include<stdio.h>

int func() {
    static int count;
    count++;
    return count;
}

int main(int argc, char *argv[]) {

    printf("%i\n", func());
    printf("%i\n", func());
    return 0;
}