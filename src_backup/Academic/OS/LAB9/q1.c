#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_ITERATIONS 100000

int counter = 0;         
sem_t m;             

void* increment(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        sem_wait(&m);    
        counter++;           
        sem_post(&m);   
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    sem_init(&m, 0, 1);
    
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&m);

    printf("Final Counter Value: %d\n", counter);
    return 0;
}