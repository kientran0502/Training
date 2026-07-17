// #include <limits.h>
// #include <stdio.h>

// int main(void)
// {
//     printf("PIPE_BUF = %d\n", PIPE_BUF);
//     return 0;
// }



// #include <stdio.h>
// #include <sys/wait.h>
// #include <string.h>
// #include <unistd.h>
// #include <stdlib.h>
// // #include "tlpi_hdr.h"

// #define BUF_SIZE 10

// int main(int argc, char *argv[]) 
// {
//     int pfd[2];          /* File descriptors của pipe: pfd[0] là đọc, pfd[1] là ghi */
//     char buf[BUF_SIZE];
//     ssize_t numRead;

//     if (argc != 2 || strcmp(argv[1], "--help") == 0) {
//         printf("Usage: %s string\n", argv[0]);
//         exit(EXIT_FAILURE);
//     }

//     /* 1. Tạo đường ống (Pipe) */
//     if (pipe(pfd) == -1) {
//         printf("pipe");
//         exit(EXIT_FAILURE);
//     }

//     /* 2. Tạo tiến trình con */
//     switch (fork()) {
//         case -1:
//             printf("fork");
//             exit(EXIT_FAILURE);

//         case 0: /* --- TIẾN TRÌNH CON (Đọc dữ liệu từ pipe) --- */
//             /* Đóng đầu GHI vì tiến trình con không dùng đến */
//             if (close(pfd[1]) == -1) {
//                 printf("close - child write end");
//                 exit(EXIT_FAILURE);
//             }

//             /* Vòng lặp đọc dữ liệu từ pipe và in ra stdout */
//             for (;;) { 
//                 numRead = read(pfd[0], buf, BUF_SIZE);
//                 if (numRead == -1) {
//                     printf("read");
//                     exit(EXIT_FAILURE);
//                 }
//                 if (numRead == 0) {
//                     break; /* Gặp EOF (khi cha đóng đầu ghi) -> Thoát vòng lặp */
//                 } 

//                 /* Ghi dữ liệu vừa đọc được ra màn hình (stdout) */
//                 if (write(STDOUT_FILENO, buf, numRead) != numRead) {
//                     printf("child - partial/failed write");
//                     exit(EXIT_FAILURE);
//                 }
//             }

//             write(STDOUT_FILENO, "\n", 1);
            
//             /* Đóng đầu ĐỌC trước khi thoát */
//             if (close(pfd[0]) == -1) {
//                 printf("close - child read end");
//                 exit(EXIT_FAILURE);
//             }
//             _exit(EXIT_SUCCESS);

//         default: /* --- TIẾN TRÌNH CHA (Ghi dữ liệu vào pipe) --- */
//             /* Đóng đầu ĐỌC vì tiến trình cha không dùng đến */
//             if (close(pfd[0]) == -1) {
//                 printf("close - parent read end");
//                 exit(EXIT_FAILURE);
//             }

//             /* Ghi chuỗi tham số truyền từ terminal (argv[1]) vào pipe */
//             if (write(pfd[1], argv[1], strlen(argv[1])) != (ssize_t)strlen(argv[1])) {
//                 printf("parent - partial/failed write");
//                 exit(EXIT_FAILURE);
//             }

//             /* Đóng đầu GHI. Hành động này sẽ gửi tín hiệu EOF đến tiến trình con */
//             if (close(pfd[1]) == -1) {
//                 printf("close - parent write end");
//                 exit(EXIT_FAILURE);
//             }

//             /* Chờ tiến trình con kết thúc để tránh tạo ra tiến trình zombie */
//             wait(NULL); 
//             exit(EXIT_SUCCESS);
//     }
// }





// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/wait.h>

// #define MSG_SIZE 4094

// int main()
// {
//     int fd[2];
//     pipe(fd);

//     if (fork() == 0)
//     {
//         close(fd[0]);

//         char buf[MSG_SIZE];
//         memset(buf, 'A', sizeof(buf));

//         for (int i = 0; i < 100; i++)
//             write(fd[1], buf, sizeof(buf));

//         exit(0);
//     }

//     if (fork() == 0)
//     {
//         close(fd[0]);

//         char buf[MSG_SIZE];
//         memset(buf, 'B', sizeof(buf));

//         for (int i = 0; i < 100; i++)
//             write(fd[1], buf, sizeof(buf));

//         exit(0);
//     }

//     close(fd[1]);

//     // char buf[MSG_SIZE];

//     // while (read(fd[0], buf, sizeof(buf)) > 0)
//     // {
//     //     printf("%.20s\n", buf);
//     //     fflush(stdout);
//     // }
//     sleep(3);
// char buf[4096];
// ssize_t n;

// while ((n = read(fd[0], buf, sizeof(buf))) > 0)
// {
//     char first = buf[0];

//     int ok = 1;

//     for (int i = 1; i < n; i++)
//     {
//         if (buf[i] != first)
//         {
//             ok = 0;
//             printf("Mixed! at byte %d (%c -> %c)\n",
//                    i, first, buf[i]);
//             break;
//         }
//     }

//     if (ok)
//         printf("%c x %ld\n", first, n);
// }
//     wait(NULL);
//     wait(NULL);
// }


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

void print_fd_info(const char *who, int fd)
{
    char path[PATH_MAX];
    char target[PATH_MAX];

    snprintf(path, sizeof(path), "/proc/%d/fd/%d", getpid(), fd);

    ssize_t len = readlink(path, target, sizeof(target) - 1);
    if (len == -1) {
        perror("readlink");
        exit(EXIT_FAILURE);
    }

    target[len] = '\0';

    printf("[%s] PID = %d\n", who, getpid());
    printf("[%s] fd = %d\n", who, fd);
    printf("[%s] %s -> %s\n\n", who, path, target);
}

int main(void)
{
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    printf("Before fork(): read=%d write=%d\n\n",
            pipefd[0], pipefd[1]);

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        print_fd_info("Child(Read)", pipefd[0]);
        print_fd_info("Child(Write)", pipefd[1]);
        exit(EXIT_SUCCESS);
    } else {
        print_fd_info("Parent(Read)", pipefd[0]);
        print_fd_info("Parent(Write)", pipefd[1]);

        wait(NULL);
    }

    return 0;
}