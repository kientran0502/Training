#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdint.h>
#include "lib.h"

#define PI 3.14

typedef struct
{
    char name[64];
    uint8_t id;
} SinhVien_t;

extern int g_number;

void my_func(void);


#endif



