// #include <stdio.h>
// #include <stdlib.h>

// int main(int argc, char *argv[])
// {
//     int j;
//     for (j = 0; j < argc; j++)
//     printf("argv[%d] = %s\n", j, argv[j]);

//     exit(EXIT_SUCCESS);
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// static int idata = 111; 

// int main(int argc, char *argv[])
// {
//     int istack = 222; 

//     pid_t childPid;

//     switch (childPid = fork()) 
//     {

//         case -1:
//             printf("fork is fail\n");
//         break;

//         case 0:
//             idata *= 3;
//             istack *= 3;
//         break;

//         default:
//             sleep(3); 
//         break;
//     }

//     printf("PID=%ld %s idata=%d istack=%d\n",(long) getpid(), (childPid == 0) ? "(child)" : "(parent)", idata, istack);

//     exit(EXIT_SUCCESS);
// }


#include <stdlib.h>
#include <stdio.h>

static void atexitFunc1(void)
{
    printf("atexit function 1 called\n");
}

static void atexitFunc2(void)
{
    printf("atexit function 2 called\n");
}

int main(int argc, char *argv[])
{
    if (atexit(atexitFunc1) != 0)
        printf("atexit 1 error");

    if (atexit(atexitFunc2) != 0)
        printf("atexit 2 error");

    printf ("Hello World\n");

    exit(EXIT_SUCCESS);
}
