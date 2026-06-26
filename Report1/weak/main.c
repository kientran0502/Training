
// void print_x(void);

// int main(void)
// {
//     print_x();
//     return 0;
// }


#include <stdio.h>
#include <stdbool.h>

// int a = 5;
// int b = 0;

struct S {
    unsigned int x : 3;
};

int main()
{
    struct S s;
    s.x = 10;
    printf("%d\n", s.x);   

    // printf("%d\n", !b);   // 1
    // printf("%d\n", ~a);
    return 0;
}