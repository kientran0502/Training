#include "people.h"

void people_init(someone_t *people)
{
    if(people == NULL || people->type == NULL)
    {
        printf("People is NULL");
        return;
    }

    switch(people->type)
    {
        case "anxin":
            people->income = "tuytam";
            people->action = cadge;
            break;
        
        case "antrom":
            people->income = "henxui";
            people->action = stole;
            break;

        case "congnhan":
            people->income = 500000;
            people->action = work;
            break;    
        
        default:
            printf("people is not defined");
            break;

    }
}

void cadge(someone_t *people)
{
    printf("anxin: lam on lam phuoc\n");
    // dua vao text
}

void stole(someone_t *people)
{
    printf("antrom: cuop!!!\n");
    // dua vao text
}

void work(someone_t *people)
{
    printf("congnhan: income is %d\n", people->salary);
    // dua vao text
}