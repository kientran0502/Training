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

#include <stdio.h>

// Alignment requirements
// (typical 32 bit machine)

// char         1 byte
// short int    2 bytes
// int          4 bytes
// double       8 bytes

// structure A
typedef struct structa_tag
{
    char c;
    short int s;
}__attribute__((packed)) structa_t;

// structure B
typedef struct structb_tag
{
    short int s;
    char c;
    int i;
}__attribute__((packed)) structb_t;

// structure C
typedef struct structc_tag
{
    char c;
    double d;
    int s;
}__attribute__((packed)) structc_t;

// structure D
typedef struct structd_tag
{
    double d;
    int s;
    char c;
}__attribute__((packed)) structd_t;

int main()
{
    printf("sizeof(structa_t) = %lu\n", sizeof(structa_t));
    printf("sizeof(structb_t) = %lu\n", sizeof(structb_t));
    printf("sizeof(structc_t) = %lu\n", sizeof(structc_t));
    printf("sizeof(structd_t) = %lu\n", sizeof(structd_t));

    return 0;
}