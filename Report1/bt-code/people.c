#include "people.h"


void cadge(someone_t *people, FILE *file)
{
    printf("anxin: lam on lam phuoc\n");
    fwrite("anxin: lam on lam phuoc\n", 1, 24, file);
}

void stole(someone_t *people, FILE *file)
{
    printf("antrom: cuop!!!\n");
    fwrite("antrom: cuop!!!\n", 1, 16, file);
}

void work(someone_t *people, FILE *file)
{
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "congnhan: income is %d\n", people->income.salary);
    printf("%s", buffer);
    fwrite(buffer, 1, strlen(buffer), file);
}

