#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "people.h"

someone_t people[MAX_PEOPLE] = {0};

bool people_create(someone_t *people, uint8_t type);

int main()
{
    FILE *file = fopen("output.txt", "w");

    if(file == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }

    for(int i = 0; i < MAX_PEOPLE; i++)
    {
        uint8_t typePeople = rand() % 3;
        people_create(&people[i], typePeople);
        people[i].action(&people[i], file);
    }
    
    fclose(file);
    
    return 0;
}

bool people_create(someone_t *people, uint8_t type)
{
    if(people == NULL)
    {
        printf("People is NULL\n");
        return false;
    }
    
    switch(type)
    {
        case 0:
            strcpy(people->type, "anxin");
            strcpy(people->income.str, "tuytam");
            people->action = cadge;
           break; 
        
        case 1:
            strcpy(people->type, "antrom");
            strcpy(people->income.str, "henxui");
            people->action = stole;
           break;

        case 2:
            strcpy(people->type, "congnhan");
            people->income.salary = 50000;
            people->action = work;
           break;

        default:
            printf("khong co loai nguoi\n");
            break;
    }
    
    return true;
}
