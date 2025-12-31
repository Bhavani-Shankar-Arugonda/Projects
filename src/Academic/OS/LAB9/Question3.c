#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5   // number of philosophers

sem_t chopstick[N];

void* philosopher(void* arg)
{
    int i = (int)(long)arg;

    while (1)
    {
        printf("Philosopher %d is thinking...\n", i);
        sleep(1);

        // pick left chopstick
        sem_wait(&chopstick[i]);
        printf("Philosopher %d picked left chopstick %d\n", i, i);

        // pick right chopstick
        sem_wait(&chopstick[(i + 1) % N]);
        printf("Philosopher %d picked right chopstick %d\n", i, (i + 1) % N);

        // eat
        printf("Philosopher %d is eating...\n", i);
        sleep(2);

        // release chopsticks
        sem_post(&chopstick[i]);
        sem_post(&chopstick[(i + 1) % N]);
        printf("Philosopher %d put down both chopsticks\n", i);
    }
}

int main()
{
    pthread_t ph[N];

    // initialize all chopstick semaphores to 1
    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    // create philosopher threads
    for (int i = 0; i < N; i++)
        pthread_create(&ph[i], NULL, philosopher, (void*)(long)i);

    // join threads (never ends)
    for (int i = 0; i < N; i++)
        pthread_join(ph[i], NULL);

    // destroy semaphores (never reached)
    for (int i = 0; i < N; i++)
        sem_destroy(&chopstick[i]);

    return 0;
}
