// #include <sys/mman.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include "tlpi_hdr.h"

// int
// main(int argc, char *argv[])
// {
//     char *addr;
//     int fd;
//     struct stat sb;

//     if (argc != 2 || strcmp(argv[1], "--help") == 0)
//         usageErr("%s file\n", argv[0]);

//     fd = open(argv[1], O_RDONLY);
//     if (fd == -1)
//         errExit("open");

//     /* Lấy kích thước của tệp và sử dụng nó để xác định
//        kích thước vùng ánh xạ cũng như số byte cần ghi */

//     if (fstat(fd, &sb) == -1)
//         errExit("fstat");

//     addr = mmap(NULL, sb.st_size, PROT_READ,
//                 MAP_PRIVATE, fd, 0);

//     if (addr == MAP_FAILED)
//         errExit("mmap");

//     if (write(STDOUT_FILENO, addr, sb.st_size) != sb.st_size)
//         fatal("partial/failed write");

//     exit(EXIT_SUCCESS);
// }


#ifdef USE_MAP_ANON
#define _BSD_SOURCE      /* Get MAP_ANONYMOUS definition */
#endif

#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int *addr;    /* Pointer to shared memory region */

#ifdef USE_MAP_ANON            /* Use MAP_ANONYMOUS */

    addr = mmap(NULL,
                sizeof(int),
                PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS,
                -1,
                0);

    if (addr == MAP_FAILED)
        errExit("mmap");

#else                          /* Map /dev/zero */

    int fd;

    fd = open("/dev/zero", O_RDWR);
    if (fd == -1)
        errExit("open");

    addr = mmap(NULL,
                sizeof(int),
                PROT_READ | PROT_WRITE,
                MAP_SHARED,
                fd,
                0);

    if (addr == MAP_FAILED)
        errExit("mmap");

    if (close(fd) == -1)       /* No longer needed */
        errExit("close");

#endif

    *addr = 1;                 /* Initialize integer in mapped region */

    switch (fork()) {

    case -1:
        errExit("fork");

    case 0:                    /* Child */

        printf("Child started, value = %d\n", *addr);

        (*addr)++;

        if (munmap(addr, sizeof(int)) == -1)
            errExit("munmap");

        exit(EXIT_SUCCESS);

    default:                   /* Parent */

        if (wait(NULL) == -1)
            errExit("wait");

        printf("In parent, value = %d\n", *addr);

        if (munmap(addr, sizeof(int)) == -1)
            errExit("munmap");

        exit(EXIT_SUCCESS);
    }
}