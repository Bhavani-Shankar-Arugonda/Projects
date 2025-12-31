#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readcount = 0;
int writecount = 0;

// Semaphores from your slide:
sem_t x;     // protects readcount
sem_t y;     // protects writecount
sem_t z;     // queue fairness for readers
sem_t rsem;  // allows or blocks readers
sem_t wsem;  // allows or blocks writers

void* reader(void* arg)
{
    for (int i = 0; i < 20; i++)
    {
        // Entry section (from your slide)
        sem_wait(&z);
        sem_wait(&rsem);
        sem_wait(&x);

        readcount++;
        if (readcount == 1)
            sem_wait(&wsem);   // first reader blocks writers

        sem_post(&x);
        sem_post(&rsem);
        sem_post(&z);

        // CRITICAL SECTION (actual reading)
        printf("Reader reading %d\n", i);
        //usleep(150000); // simulate reading

        // Exit section
        sem_wait(&x);
        readcount--;
        if (readcount == 0)
            sem_post(&wsem);   // last reader unblocks writers
        sem_post(&x);
    }
    return NULL;
}

void* writer(void* arg)
{
    for (int i = 0; i < 20; i++)
    {
        // Entry section (from your slide)
        sem_wait(&y);
        writecount++;
        if (writecount == 1)
            sem_wait(&rsem);   // first writer blocks readers
        sem_post(&y);

        // Critical section
        sem_wait(&wsem);          // writer waits for exclusive access
        printf("Writer writing %d\n", i);
        //usleep(200000);           // simulate writing
        sem_post(&wsem);

        // Exit section
        sem_wait(&y);
        writecount--;
        if (writecount == 0)
            sem_post(&rsem);       // last writer unblocks readers
        sem_post(&y);
    }
    return NULL;
}

int main()
{
    // Initialize all semaphores exactly as in slide:
    sem_init(&x, 0, 1);
    sem_init(&y, 0, 1);
    sem_init(&z, 0, 1);
    sem_init(&rsem, 0, 1);
    sem_init(&wsem, 0, 1);

    pthread_t r1, r2, w1, w2;

    // Create multiple readers/writers to show correctness
    pthread_create(&w1, NULL, writer, NULL);
    pthread_create(&r1, NULL, reader, NULL);
    //pthread_create(&r2, NULL, reader, NULL);
    
    //pthread_create(&w2, NULL, writer, NULL);
    pthread_join(w1, NULL);
    pthread_join(r1, NULL);
    //pthread_join(r2, NULL);
    
    //pthread_join(w2, NULL);

    sem_destroy(&x);
    sem_destroy(&y);
    sem_destroy(&z);
    sem_destroy(&rsem);
    sem_destroy(&wsem);

    return 0;
}
