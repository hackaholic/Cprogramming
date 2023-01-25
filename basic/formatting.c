#include <stdio.h>
#include <stdarg.h>



int main() {

    // formatting practice, printf returns number of character printed
    printf(":%s:\n", "Hello World");
    printf(":%30s:\n", "Hello World");   // right alignment
    printf(":%-30s:\n", "Hello World");  // Left alignment
    printf(":%.5s:\n", "Hello World");   // only take 5 char
    printf(":%20.5s:\n", "Hello World");

    char arr[20];
    // sprintf same as printf but stores the formatted output in string
    // sprintf(char *string, char *fmt, arg1, ag2,....)
    sprintf(arr, "Hello %s %s", "Coco", "Mini");
    printf("%s\n", arr);

    // scanf(char *fmt, ....) -> reads chracter from standard input
    // returns no of character read
    int i, n;
    printf("Enter an interger: ");
    n = scanf("%i", &i);
    if (n)
        printf("Ok\n");
    else 
       printf("Wrong input type\n");

    // sscanf(char *string, char *fmt, arg1, arg2, ...)
    // read character from input string
    char a[10], b[10], c[10];
    n = sscanf(arr, "%s %s %s", a, b, c);
    printf("%s %s %s\n", a, b ,c);


    // more on scanf 
    
    int d;
    char str[50];
    /*
        for limit use width like %5d, it will take only 5 digit input

        so input 123456789 it will only read 12345
        for string input hellotherecoco, it will read hellothere
    */
    printf("enter a long digit, it will only take 1st 5 digit: \n");
    scanf("%5d", &d);
    printf("%d\n", d);
    
    while(getchar() != 10);       // this is to flush remaining digit on stdin before moving to next

    printf("Enter a string of at least 10 charer long:\n");
    scanf("%10s", str);
    printf("%s\n", str);

    /*
        selective selection using []
        %[a-z] will only select letter contain a-z
        '^' is used for up to
        %[^\n] will pickup all upto \n

        * is used to exclude
        %*c, it will execude a char
        
        %*[^,]  it will execude all upto , 

        %n record the scanf offset
        %ms or %mi for dynamic allocation
    */ 

    sscanf("(abcd, 10)", "(%50[^,], %i %n", str, &d, &n);
    printf("%s; %i, offset: %i\n", str, d, n);

    while(getchar() != 10);  //always clear the stdin before moving to next, comment this to test.
    char *s;
    printf("Input string: ");
    scanf("%ms", &s);       //  here scanf will allocate memory for the pointer *s
    printf("\n%s\n", s);

    return 0;

}