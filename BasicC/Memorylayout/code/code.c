#include <stdio.h>
int main() 
{
    void * addr = (void *) 0x0;

    // in order to print out what exists at that pointer, we must dereference the pointer
    // but C doesn't know how to handle a value of void type
    // which means, we recast the void pointer to a char pointer
    // a char is some arbitrary byte, so hopefully it's a printable ASCII value
    // actually, we don't need to hope, because we have made printf specifically print the hex representation of the char, therefore it does not need to be a printable ascii value
    printf("0x%x\n", ((char *) addr)[0]); // prints 0x0
    printf("0x%x\n", ((char *) addr)[1]); // prints 0x1
    printf("0x%x\n", ((char *) addr)[2]); // prints 0x2
}




#include <sys/wait.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int numChildren, j;
    pid_t childPid;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [num-children]\n", argv[0]);

    numChildren = (argc > 1) ?
            getInt(argv[1], GN_GT_0, "num-children") : 1;

    setbuf(stdout, NULL);    /* Tắt bộ đệm của stdout */

    for (j = 0; j < numChildren; j++) {

        switch (childPid = fork()) {

        case -1:
            errExit("fork");

        case 0:
            printf("%d child\n", j);
            _exit(EXIT_SUCCESS);

        default:
            printf("%d parent\n", j);

            wait(NULL);      /* Đợi process con kết thúc */

            break;
        }
    }

    exit(EXIT_SUCCESS);
}