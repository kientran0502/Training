#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

static sem_t sem_hello;
static sem_t sem_world;

static void *helloFunc(void *arg)
{
    while(1)
    {
        if(sem_wait(&sem_hello) != 0)
        {
            printf("sem_wait hellofunc failed\n");
            // fflush(stdout);
            return NULL;
        }
        printf("Hello ");
        // fflush(stdout);
        sleep(1);
        if(sem_post(&sem_world) != 0)
        {
            printf("sem_post hellofunc failed\n");
            return NULL;
        }
    }
}

static void *worldFunc(void *arg)
{
    while(1)
    {
        if(sem_wait(&sem_world) != 0)
        {
            printf("sem_wait worldfunc failed\n");
            // fflush(stdout);
            return NULL;
        }
        printf("World!\n");
        sleep(1);
        if(sem_post(&sem_hello) != 0)
        {
            printf("sem_post worldfunc failed\n");
            // fflush(stdout);
            return NULL;
        }
    }

}

int main()
{
    pthread_t t1, t2;

    if(sem_init(&sem_hello, 0, 1) != 0)
    {
        printf("sem_init failed\n");
        return 1;
    }

    if(sem_init(&sem_world, 0, 0) != 0)
    {
        printf("sem_init failed\n");
        return 1;
    }

    int s = pthread_create(&t1, NULL, helloFunc, NULL);
    if(s != 0)
        fprintf(stderr, "pthread_create failed with error code: %d\n", s);

    s = pthread_create(&t2, NULL, worldFunc, NULL);
    if(s != 0)
        fprintf(stderr, "pthread_create failed with error code: %d\n", s);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}