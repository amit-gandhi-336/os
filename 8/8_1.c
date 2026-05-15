#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];

int in = 0;
int out = 0;

sem_t empty, full, mutex;

/* Producer */

void *producer(void *arg)
{
    for(int i = 1; i <= 10; i++)
    {
        sem_wait(&empty);

        sem_wait(&mutex);

        buffer[in] = i;

        printf("Producer produced item %d\n", i);

        in = (in + 1) % SIZE;

        sem_post(&mutex);

        sem_post(&full);

        sleep(1);
    }

    return NULL;
}

/* Consumer */

void *consumer(void *arg)
{
    int id = *(int *)arg;

    for(int i = 0; i < 3; i++)
    {
        sem_wait(&full);

        sem_wait(&mutex);

        int item = buffer[out];

        printf("Consumer %d consumed item %d\n",
               id, item);

        out = (out + 1) % SIZE;

        sem_post(&mutex);

        sem_post(&empty);

        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t p, c1, c2, c3;

    int id1 = 1;
    int id2 = 2;
    int id3 = 3;

    /* Initialize semaphores */

    sem_init(&empty, 0, SIZE);

    sem_init(&full, 0, 0);

    sem_init(&mutex, 0, 1);

    /* Create threads */

    pthread_create(&p, NULL,
                   producer, NULL);

    pthread_create(&c1, NULL,
                   consumer, &id1);

    pthread_create(&c2, NULL,
                   consumer, &id2);

    pthread_create(&c3, NULL,
                   consumer, &id3);

    /* Wait */

    pthread_join(p, NULL);

    pthread_join(c1, NULL);

    pthread_join(c2, NULL);

    pthread_join(c3, NULL);

    /* Destroy semaphores */

    sem_destroy(&empty);

    sem_destroy(&full);

    sem_destroy(&mutex);

    return 0;
}