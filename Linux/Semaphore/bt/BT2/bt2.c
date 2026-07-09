#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// int buffer[10];
pthread_t producer1_thread, producer2_thread, 
            consumer1_thread, consumer2_thread, consumer3_thread;

sem_t bracket_empty_slots, bracket_used_slots;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int num_empty_slots = 10;

void *producer1(void *arg)
{
    while(1)
    {
        
        sem_wait(&bracket_empty_slots);
        pthread_mutex_lock(&mutex);
        printf("Producer 1 produced an item, bracket_empty_slots: %d\n", --num_empty_slots);
        pthread_mutex_unlock(&mutex);
        sem_post(&bracket_used_slots);       
        usleep(100000);
    }
}

void *producer2(void *arg)
{
    while(1)
    {
        
        sem_wait(&bracket_empty_slots);    
        pthread_mutex_lock(&mutex);   
        printf("Producer 2 produced an item, bracket_empty_slots: %d\n", --num_empty_slots);
        pthread_mutex_unlock(&mutex);
        sem_post(&bracket_used_slots);
        usleep(100000);
    }
}

void *consumer1(void *arg)
{
    while(1)
    {
        
        sem_wait(&bracket_used_slots);
        pthread_mutex_lock(&mutex);  
        printf("Consumer 1 consumed an item, bracket_empty_slots: %d\n", ++num_empty_slots);
        pthread_mutex_unlock(&mutex);
        sem_post(&bracket_empty_slots);
        usleep(200000);
    }
}

void *consumer2(void *arg)
{
    while(1)
    {
        
        sem_wait(&bracket_used_slots);
        pthread_mutex_lock(&mutex);
        printf("Consumer 2 consumed an item, bracket_empty_slots: %d\n", ++num_empty_slots);
        pthread_mutex_unlock(&mutex);
        sem_post(&bracket_empty_slots);
        usleep(200000);
    }
}

void *consumer3(void *arg)
{
    while(1)
    {
        
        sem_wait(&bracket_used_slots);
        pthread_mutex_lock(&mutex);
        printf("Consumer 3 consumed an item, bracket_empty_slots: %d\n", ++num_empty_slots);
        pthread_mutex_unlock(&mutex);
        sem_post(&bracket_empty_slots);
        usleep(200000);
    }
}

int main()
{
    if(sem_init(&bracket_empty_slots, 0, 10) == -1)
    {
        printf("sem_init failed\n");
        return 1;
    }

    if(sem_init(&bracket_used_slots, 0, 0) == -1)
    {
        printf("sem_init failed\n");
        return 1;
    }

    pthread_create(&producer1_thread, NULL, producer1, NULL);
    pthread_create(&producer2_thread, NULL, producer2, NULL);
    pthread_create(&consumer1_thread, NULL, consumer1, NULL);
    pthread_create(&consumer2_thread, NULL, consumer2, NULL);
    pthread_create(&consumer3_thread, NULL, consumer3, NULL);

    pthread_join(producer1_thread, NULL);
    pthread_join(producer2_thread, NULL);  
    pthread_join(consumer1_thread, NULL);
    pthread_join(consumer2_thread, NULL);
    pthread_join(consumer3_thread, NULL);

    
    return 0;
}