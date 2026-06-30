// #include <pthread.h>
// #include "stdio.h"
// #include <stdlib.h>
// #include <string.h>

// static void *
// threadFunc(void *arg)
// {
//     char *s = (char *) arg;

//     printf("%s", s);

//     return (void *) strlen(s);
// }

// int
// main(int argc, char *argv[])
// {
//     pthread_t t1;
//     void *res;
//     int s;

//     s = pthread_create(&t1, NULL, threadFunc, "Hello world\n");
//     if (s != 0) {
//         fprintf(stderr, "pthread_create failed with error code: %d\n", s);
//         exit(EXIT_FAILURE);
//     }

//     printf("Message from main()\n");

//     s = pthread_join(t1, &res);

//     if (s != 0) {
//         fprintf(stderr, "pthread_create failed with error code: %d\n", s);
//         exit(EXIT_FAILURE);
//     }

//     printf("Thread returned %ld\n", (long) res);

//     exit(EXIT_SUCCESS);
// }


#include <pthread.h>
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void * threadFunc(void *arg)
{
    int loops = *((int *) arg);
    int loc, j, s;

    for (j = 0; j < loops; j++) {
        s = pthread_mutex_lock(&mtx);
        loc = glob;
        loc++;
        glob = loc;
        s = pthread_mutex_unlock(&mtx); 
    }

    return NULL;
}

int
main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;

    loops = atoi(argv[1]); 
    if (loops <= 0) {
        fprintf(stderr, "num-loops must be > 0\n");
        exit(EXIT_FAILURE);
    }

    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0)
        fprintf(stderr, "pthread_create failed with error code: %d\n", s);

    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0)
        fprintf(stderr, "pthread_create failed with error code: %d\n", s);

    s = pthread_join(t1, NULL);
    if (s != 0)
        fprintf(stderr, "pthread_join failed with error code: %d\n", s);

    s = pthread_join(t2, NULL);
    if (s != 0)
        fprintf(stderr, "pthread_join failed with error code: %d\n", s);

    printf("glob = %d\n", glob);

    exit(EXIT_SUCCESS);
}