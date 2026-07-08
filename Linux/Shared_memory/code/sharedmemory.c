// /* pshm_create.c */

// #include <sys/stat.h>
// #include <fcntl.h>
// #include <sys/mman.h>

// #include "tlpi_hdr.h"

// static void
// usageError(const char *progName)
// {
//     fprintf(stderr, "Usage: %s [-cx] name size [octal-perms]\n", progName);
//     fprintf(stderr, "    -c    Create shared memory (O_CREAT)\n");
//     fprintf(stderr, "    -x    Create exclusively (O_EXCL)\n");
//     exit(EXIT_FAILURE);
// }

// int
// main(int argc, char *argv[])
// {
//     int flags, opt, fd;
//     mode_t perms;
//     size_t size;
//     void *addr;

//     flags = O_RDWR;

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

//     if (optind + 1 >= argc)
//         usageError(argv[0]);

//     size = getLong(argv[optind + 1], GN_ANY_BASE, "size");

//     perms = (argc <= optind + 2)
//                 ? (S_IRUSR | S_IWUSR)
//                 : getLong(argv[optind + 2], GN_BASE_8, "octal-perms");

//     /* Create shared memory object and set its size */

//     fd = shm_open(argv[optind], flags, perms);
//     if (fd == -1)
//         errExit("shm_open");

//     if (ftruncate(fd, size) == -1)
//         errExit("ftruncate");

//     /* Map shared memory object */

//     addr = mmap(NULL,
//                 size,
//                 PROT_READ | PROT_WRITE,
//                 MAP_SHARED,
//                 fd,
//                 0);

//     if (addr == MAP_FAILED)
//         errExit("mmap");

//     exit(EXIT_SUCCESS);
// }










// 

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int fd;
    char *addr;
    struct stat sb;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s shm-name\n", argv[0]);

    fd = shm_open(argv[1], O_RDONLY, 0);      /* Mở đối tượng đã tồn tại */
    if (fd == -1)
        errExit("shm_open");

    /* Sử dụng kích thước của shared memory object làm đối số chiều dài
       cho mmap() và làm số byte cần ghi bằng write() */

    if (fstat(fd, &sb) == -1)
        errExit("fstat");

    addr = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
        errExit("mmap");

    if (close(fd) == -1)                      /* Không còn cần 'fd' nữa */
        errExit("close");

    write(STDOUT_FILENO, addr, sb.st_size);
    printf("\n");

    exit(EXIT_SUCCESS);
}