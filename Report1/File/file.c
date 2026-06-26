// int open(const char *path, int flags);
// int open(const char *path, int flags, mode_t mode);

// ssize_t read(int fd, void *buf, size_t count);

// ssize_t write(int fd, const void *buf, size_t count);

// int close(int fd);

// #include <stdio.h>


// int x;
// int y;

// int f(double x)
// {
//     double y;
// }


// struct Student
// {
//     char name[50];
//     int age;
// };

// struct Student s1;

// struct Student s1 = {"Kien", 22};

// struct Student s2 =
// {
//     .age = 22,
//     .name = "Kien"
// };



// s1.age = 20;
// printf("%d\n", s1.age);



// #include <stdio.h>

// // Structure declaration
// struct Point {
//     int x, y;
// };

// int main() {
//     struct Point p = { 1, 2 };

//     // ptr is a pointer to structure p
//     struct Point* ptr = &p;

//     // Accessing structure members using structure pointer
//     printf("%d %d", ptr->x, ptr->y);

//     return 0;
// }

// #include <stdio.h>

// // Alignment requirements
// // (typical 32 bit machine)

// // char         1 byte
// // short int    2 bytes
// // int          4 bytes
// // double       8 bytes

// // structure A
// typedef struct structa_tag
// {
//     char c;
//     short int s;
// } structa_t;

// // structure B
// typedef struct structb_tag
// {
//     short int s;
//     char c;
//     int i;
// } structb_t;

// // structure C
// typedef struct structc_tag
// {
//     char c;
//     double d;
//     int s;
// } structc_t;

// // structure D
// typedef struct structd_tag
// {
//     double d;
//     int s;
//     char c;
// } structd_t;

// typedef union unionE_tag
// {
//     double d;
//     int s;
//     char c;
// } unionE_t;

// int main()
// {
//     // printf("sizeof(structa_t) = %lu\n", sizeof(structa_t));
//     // printf("sizeof(structb_t) = %lu\n", sizeof(structb_t));
//     // printf("sizeof(structc_t) = %lu\n", sizeof(structc_t));
//     printf("sizeof(structd_t) = %lu\n", sizeof(structd_t));

//     printf("sizeof(unionE_t) = %lu\n", sizeof(unionE_t));

//     return 0;
// }


// #include <stdio.h>
// #include <string.h>

// typedef struct structa_tag {
//     char c;
//     short int s;
// } structa_t;

// typedef struct structb_tag {
//     short int s;
//     char c;
//     int i;
// } structb_t;

// typedef struct structc_tag {
//     char c;
//     double d;
//     int s;
// } structc_t;

// typedef struct structd_tag {
//     double d;
//     int s;
//     char c;
// } structd_t;

// // Hàm hỗ trợ in từng byte của bộ nhớ dưới dạng Hex
// void print_mem(unsigned char *ptr, size_t size, const char *name) {
//     printf("%s (%zu bytes): [ ", name, size);
//     for (size_t i = 0; i < size; i++) {
//         printf("%02X ", ptr[i]);
//     }
//     printf("]\n");
// }

// int main() {
//     // 1. Khảo sát Cấu trúc A
//     structa_t a;
//     memset(&a, 0x00, sizeof(a)); 
//     a.c = 0x11;
//     a.s = 0x2222;
//     print_mem((unsigned char*)&a, sizeof(a), "structa_t");

//     // 2. Khảo sát Cấu trúc B
//     structb_t b;
//     memset(&b, 0x00, sizeof(b));
//     b.s = 0x1111;
//     b.c = 0x22;
//     b.i = 0x33333333;
//     print_mem((unsigned char*)&b, sizeof(b), "structb_t");

//     // 3. Khảo sát Cấu trúc C
//     structc_t c;
//     memset(&c, 0x00, sizeof(c));
//     c.c = 0x11;
//     c.d = 0x2222222222222222; 
    
//     unsigned char *pd = (unsigned char*)&c.d;
//     for(int i=0; i<8; i++) pd[i] = 0xDD; 
//     c.s = 0x44444444;
//     print_mem((unsigned char*)&c, sizeof(c), "structc_t");

//     // 4. Khảo sát Cấu trúc D
//     structd_t d;
//     memset(&d, 0x00, sizeof(d));
//     unsigned char *pd2 = (unsigned char*)&d.d;
//     for(int i=0; i<8; i++) pd2[i] = 0xDD;
//     d.s = 0x44444444;
//     d.c = 0x55;
//     print_mem((unsigned char*)&d, sizeof(d), "structd_t");

//     return 0;
// }


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fd;
    char buf[6] = {0};

    fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror("open");
        return -1;
    }

    printf("Offset sau open = %ld\n", lseek(fd, 0, SEEK_CUR));

    write(fd, "HelloWorld", 10);

    printf("Offset sau write = %ld\n", lseek(fd, 0, SEEK_CUR));

    lseek(fd, 0, SEEK_SET);

    printf("Offset sau SEEK_SET = %ld\n", lseek(fd, 0, SEEK_CUR));

    read(fd, buf, 5);

    printf("Doc duoc: %s\n", buf);
    printf("Offset sau read 5 bytes = %ld\n", lseek(fd, 0, SEEK_CUR));

    lseek(fd, -2, SEEK_CUR);

    printf("Offset sau lui 2 byte = %ld\n", lseek(fd, 0, SEEK_CUR));

    read(fd, buf, 2);
    buf[2] = '\0';

    printf("Doc tiep: %s\n", buf);

    close(fd);

    return 0;
}