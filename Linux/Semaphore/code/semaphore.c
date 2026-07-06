#include <stdio.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void usageError(const char *progName)
{
    fprintf(stderr,
            "Usage: %s [-cx] name [octal-perms [value]]\n",
            progName);

    fprintf(stderr,
            " -c Create semaphore (O_CREAT)\n");

    fprintf(stderr,
            " -x Create exclusively (O_EXCL)\n");

    exit(EXIT_FAILURE);
}

// int main(int argc, char *argv[])
// {
//     int flags, opt;
//     mode_t perms;
//     unsigned int value;
//     sem_t *sem;

//     flags = 0;

//     while ((opt = getopt(argc, argv, "cx")) != -1) {
//         switch (opt) {
//         case 'c':
//             flags |= O_CREAT;
//             break;

//         case 'x':
//             flags |= O_EXCL;
//             break;

//         default:
//             usageError(argv[0]);
//         }
//     }

//     if (optind >= argc)
//         usageError(argv[0]);

//     /* Quyền mặc định là rw-------;
//        Giá trị khởi tạo mặc định của semaphore là 0 */

//     perms = (argc <= optind + 1)
//                 ? (S_IRUSR | S_IWUSR)
//                 : strtol(argv[optind + 1], NULL, 8);

//     value = (argc <= optind + 2)
//                 ? 0
//                 : strtoul(argv[optind + 2], NULL, 0);

//     sem = sem_open(argv[optind],
//                    flags,
//                    perms,
//                    value);

//     if (sem == SEM_FAILED)
//     {
//         perror("sem_open");
//         exit(EXIT_FAILURE);
//     }
        

//     exit(EXIT_SUCCESS);
// }

// int main(int argc, char *argv[])
// {
//     if (argc != 2 || strcmp(argv[1], "--help") == 0)
//         usageError("%s sem-name\n", argv[0]);

//     if (sem_unlink(argv[1]) == -1)
//     {
//         perror("sem_unlink");
//         exit(EXIT_FAILURE);
//     }

//     exit(EXIT_SUCCESS);
// }


#include <semaphore.h>
#include <pthread.h>
#include "tlpi_hdr.h"

static int glob = 0;
static sem_t sem;

static void *
threadFunc(void *arg)
{
    int loops = *((int *) arg);
    int loc, j;

    for (j = 0; j < loops; j++) {

        if (sem_wait(&sem) == -1)
            errExit("sem_wait");

        loc = glob;
        loc++;
        glob = loc;

        if (sem_post(&sem) == -1)
            errExit("sem_post");
    }

    return NULL;
}

int
main(int argc, char *argv[])
{
    pthread_t t1, t2;
    int loops, s;

    loops = (argc > 1)
                ? getInt(argv[1], GN_GT_0, "num-loops")
                : 10000000;

    /* Khởi tạo semaphore dùng chung giữa các thread
       với giá trị ban đầu là 1 */

    if (sem_init(&sem, 0, 1) == -1)
        errExit("sem_init");

    /* Tạo hai thread cùng tăng biến glob */

    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0)
        errExitEN(s, "pthread_create");

    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0)
        errExitEN(s, "pthread_create");

    /* Chờ hai thread kết thúc */

    s = pthread_join(t1, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");

    s = pthread_join(t2, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");

    printf("glob = %d\n", glob);

    exit(EXIT_SUCCESS);
}