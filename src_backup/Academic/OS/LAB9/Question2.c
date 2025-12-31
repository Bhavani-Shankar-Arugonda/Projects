#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 10

int buffer[SIZE];
int in = 0, out = 0;

sem_t mutex, full, empty;

void append(int item) {
    buffer[in] = item;
    in = (in + 1) % SIZE;
}

int take() {
    int item = buffer[out];
    out = (out + 1) % SIZE;
    return item;
}

void *producer(void *arg) {
    for (int i = 0; i < 20; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);

        append(i);
        printf("Produced %d\n", i);

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 20; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = take();
        printf("Consumed %d\n", item);

        sem_post(&mutex);
        sem_post(&empty);

        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&mutex, 0, 1);
    sem_init(&full,  0, 0);
    sem_init(&empty, 0, SIZE);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
