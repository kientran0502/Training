#include <stdio.h>

int x __attribute__((weak)) = 5;

void print_x(void)
{
    printf("x = %d\n", x);
}