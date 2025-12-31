#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t s;
sem_t n;
sem_t e;


void* produce()
{
    while(1)
    {
        
        sem_wait(&e);
        sem_wait(&s);

        printf("produce new thing\n");

        sem_post(&s);
        sem_post(&n);
    }
}


void* consumer()
{
    while(1)
    {
        
        sem_wait(&n);
        sem_wait(&s);

        printf("consumed thing\n");

        sem_post(&s);
        sem_post(&e);
    }
}

void main()
{
    pthread_t t1;
    pthread_t t2;

    sem_init(&s,0,1);
    sem_init(&n,0,0);
    sem_init(&e,0,5);

    pthread_create(&t1,NULL,produce,NULL);
    pthread_create(&t2,NULL,consumer,NULL);


    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    sem_destroy(&s);
    sem_destroy(&n);
    sem_destroy(&e);


}