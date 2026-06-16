#include <stdio.h>
#include "lib.h"

// if we uncomment the below line, then the program will print AGE in the output.

# define PI 3.14

#define SUM(a,b) (a + b)

const int MAX_SIZE = 100;

// #define AGE 18

int foo(int x)
{
    switch(x)
    {
        case 0: return 10;
        case 1: return 20;
        case 2: return 30;
        case 3: return 40;
        default: return -1;
    }
}

int main()
{
    printf("PI is %.2f\n", PI);

    func1();

    printf("Sum is %d\n", SUM(3,2));
	// if `AGE` is defined then print the `AGE` else print "Not Defined"
	#ifdef AGE
		printf("Age is %d\n", AGE);
	#else
		printf("Not Defined AGE\n");
	#endif

    foo(3);

	return 0;
}


