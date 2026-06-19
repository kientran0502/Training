#ifndef PEOPLE_H
#define PEOPLE_H

#include <stdint.h>

#define MAX_PEOPLE           100

typedef union
{
    char str[10];
    uint16_t salary;
} get_t;


typedef struct
{
    char type[10];
    get_t income;
    void (*action)(someone_t *people); 
} someone_t;

void people_init(someone_t *people);
void cadge(someone_t *people);
void stole(someone_t *people);
void work(someone_t *people);

#endif 