/*
  Author: Kumar Shubham
  void
  char
  short
  int
  long
  float
  double
  signed
  unsigned
  struct
  union
  enum
  typedef

*/


#include <stdio.h>
#include <stdint.h>   // int32_t

int main(int argc, char *argv[]) {
    
    printf("type and their sizes\n");
    printf("%-20s %lu\n", "char:", sizeof(char));
    printf("%-20s %lu\n", "short", sizeof(short));
    printf("%-20s %lu\n", "int", sizeof(int));
    printf("%-20s %lu\n", "long int:", sizeof(long int));
    printf("%-20s %ld\n", "double int:", sizeof(double));
    printf("%-20s %lu\n", "long long int:", sizeof(long long int));
    printf("%-20s %ld\n", "double long int:", sizeof(double long));
    printf("%-20s %lu\n", "float", sizeof(float));
    return 0;
}