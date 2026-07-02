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