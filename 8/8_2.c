#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 3

pthread_mutex_t forks[N];

/* Philosopher function */

void *philosopher(void *num)
{
    int id = *(int *)num;

    int left = id;

    int right = (id + 1) % N;

    printf("Philosopher %d is thinking\n", id);

    sleep(1);

    /* Deadlock prevention:
       Philosopher 2 picks right fork first */

    if(id == 2)
    {
        pthread_mutex_lock(&forks[right]);

        printf("Philosopher %d picked fork %d\n",
               id, right);

        pthread_mutex_lock(&forks[left]);

        printf("Philosopher %d picked fork %d\n",
               id, left);
    }
    else
    {
        pthread_mutex_lock(&forks[left]);

        printf("Philosopher %d picked fork %d\n",
               id, left);

        pthread_mutex_lock(&forks[right]);

        printf("Philosopher %d picked fork %d\n",
               id, right);
    }

    printf("Philosopher %d is eating\n", id);

    sleep(1);

    pthread_mutex_unlock(&forks[left]);

    pthread_mutex_unlock(&forks[right]);

    printf("Philosopher %d finished eating\n",
           id);

    return NULL;
}

int main()
{
    pthread_t p[N];

    int ids[N];

    /* Initialize mutex forks */

    for(int i = 0; i < N; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
    }

    /* Create philosopher threads */

    for(int i = 0; i < N; i++)
    {
        ids[i] = i;

        pthread_create(&p[i],
                       NULL,
                       philosopher,
                       &ids[i]);
    }

    /* Wait for all philosophers */

    for(int i = 0; i < N; i++)
    {
        pthread_join(p[i], NULL);
    }

    /* Destroy mutexes */

    for(int i = 0; i < N; i++)
    {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

gcc dining.c -pthread -o dining