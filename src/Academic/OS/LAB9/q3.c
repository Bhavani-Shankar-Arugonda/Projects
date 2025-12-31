#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];  // One semaphore per fork
sem_t mutex;                     // To prevent deadlock (only 4 philosophers allowed to pick forks)
pthread_t philosophers[NUM_PHILOSOPHERS];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        sem_wait(&mutex);             
        sem_wait(&forks[left]);      
        sem_wait(&forks[right]);      

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        sem_post(&forks[left]);       
        sem_post(&forks[right]);       

        printf("Philosopher %d finished eating\n", id);
    }
    return NULL;
}

int main() {
    int ids[NUM_PHILOSOPHERS];

    sem_init(&mutex, 0, NUM_PHILOSOPHERS - 1);  
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        sem_init(&forks[i], 0, 1);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosophers[i], NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        sem_destroy(&forks[i]);
    sem_destroy(&mutex);

    return 0;
}
