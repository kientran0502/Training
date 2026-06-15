#include "lib.h"

#define PI 3.14
#define DIAMETER 2

/* main function */
int main(void)
{
    int C = PI * DIAMETER;
    lib_func1(); // Call the function from the library
}


//gcc -E main.c -o main.i # Preprocessing
//gcc -S main.c -o main.s  # Compiling
//gcc -c main.s -o main.o (nm main.o  objdump -d main.o)
//gcc -c lib.c -o lib.o  
//gcc main.o lib.o -o main.exe
//./main.exe

