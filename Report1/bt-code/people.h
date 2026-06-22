#ifndef PEOPLE_H
#define PEOPLE_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_PEOPLE           10

typedef union
{
    char str[10];
    uint16_t salary;
} get_t;

typedef struct someone someone_t;

typedef struct someone
{
    char type[10];
    get_t income;
    void (*action)(someone_t *people, FILE *file); 
} someone_t;

void cadge(someone_t *people, FILE *file);
void stole(someone_t *people, FILE *file);
void work(someone_t *people, FILE *file);

#endif


