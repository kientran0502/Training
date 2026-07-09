#include <stdio.h>
#include <pthread.h>
#include <mqueue.h>
#include <fctrl.h>

pthread_t A_thread, admin_thread, B_thread, C_thread;

void *A_function(void *arg)
{
    while(1)
    {
        printf("Thread A is running\n");
        usleep(500000);
    }
}

void *admin_function(void *arg)
{
    while(1)
    {
        printf("Admin thread is running\n");
        usleep(700000);
    }
}

void *B_function(void *arg)
{
    while(1)
    {
        printf("Thread B is running\n");
        usleep(600000);
    }
}

void *C_function(void *arg)
{
    while(1)
    {
        printf("Thread C is running\n");
        usleep(800000);
    }
}

int main()
{
    pthread_create(&A_thread, NULL, A_function, NULL);
    pthread_create(&admin_thread, NULL, admin_function, NULL);
    pthread_create(&B_thread, NULL, B_function, NULL);
    pthread_create(&C_thread, NULL, C_function, NULL);

    pthread_join(A_thread, NULL);
    pthread_join(admin_thread, NULL);
    pthread_join(B_thread, NULL);
    pthread_join(C_thread, NULL);

    char input[100] = {0};

    mq_open("/mq", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, NULL);

    while(1)
    {
        printf("Enter a message: ");
        scanf("%s", input);
        switch(input[0])
        {
            case 'A':
            mq_send(mesage_queue, "
                
                
                ", 4, 1);
            break;

            case 'B':
            break;

            case 'C':
            break;

            default:
            break;
        }
    }

    return 0;
}