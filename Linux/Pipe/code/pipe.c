// #include <limits.h>
// #include <stdio.h>

// int main(void)
// {
//     printf("PIPE_BUF = %d\n", PIPE_BUF);
//     return 0;
// }
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
// #include "tlpi_hdr.h"

#define BUF_SIZE 10

int main(int argc, char *argv[]) 
{
    int pfd[2];          /* File descriptors của pipe: pfd[0] là đọc, pfd[1] là ghi */
    char buf[BUF_SIZE];
    ssize_t numRead;

    if (argc != 2 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: %s string\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* 1. Tạo đường ống (Pipe) */
    if (pipe(pfd) == -1) {
        printf("pipe");
        exit(EXIT_FAILURE);
    }

    /* 2. Tạo tiến trình con */
    switch (fork()) {
        case -1:
            printf("fork");
            exit(EXIT_FAILURE);

        case 0: /* --- TIẾN TRÌNH CON (Đọc dữ liệu từ pipe) --- */
            /* Đóng đầu GHI vì tiến trình con không dùng đến */
            if (close(pfd[1]) == -1) {
                printf("close - child write end");
                exit(EXIT_FAILURE);
            }

            /* Vòng lặp đọc dữ liệu từ pipe và in ra stdout */
            for (;;) { 
                numRead = read(pfd[0], buf, BUF_SIZE);
                if (numRead == -1) {
                    printf("read");
                    exit(EXIT_FAILURE);
                }
                if (numRead == 0) {
                    break; /* Gặp EOF (khi cha đóng đầu ghi) -> Thoát vòng lặp */
                } 

                /* Ghi dữ liệu vừa đọc được ra màn hình (stdout) */
                if (write(STDOUT_FILENO, buf, numRead) != numRead) {
                    printf("child - partial/failed write");
                    exit(EXIT_FAILURE);
                }
            }

            write(STDOUT_FILENO, "\n", 1);
            
            /* Đóng đầu ĐỌC trước khi thoát */
            if (close(pfd[0]) == -1) {
                printf("close - child read end");
                exit(EXIT_FAILURE);
            }
            _exit(EXIT_SUCCESS);

        default: /* --- TIẾN TRÌNH CHA (Ghi dữ liệu vào pipe) --- */
            /* Đóng đầu ĐỌC vì tiến trình cha không dùng đến */
            if (close(pfd[0]) == -1) {
                printf("close - parent read end");
                exit(EXIT_FAILURE);
            }

            /* Ghi chuỗi tham số truyền từ terminal (argv[1]) vào pipe */
            if (write(pfd[1], argv[1], strlen(argv[1])) != (ssize_t)strlen(argv[1])) {
                printf("parent - partial/failed write");
                exit(EXIT_FAILURE);
            }

            /* Đóng đầu GHI. Hành động này sẽ gửi tín hiệu EOF đến tiến trình con */
            if (close(pfd[1]) == -1) {
                printf("close - parent write end");
                exit(EXIT_FAILURE);
            }

            /* Chờ tiến trình con kết thúc để tránh tạo ra tiến trình zombie */
            wait(NULL); 
            exit(EXIT_SUCCESS);
    }
}
