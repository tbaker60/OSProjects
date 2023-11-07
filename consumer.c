// Toby Baker
// OS Project 1 Consumer file
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 20

void* consumer(void* arg) {
    while(consumed_count < MAX_ITEMS) {
        sem_wait(&full);
        sem_wait(&empty);

        int item = buffer[out];
        printf("Consumed: %d", item);
        out = (out + 1) % BUFFER_SIZE;
        ++consumed_count;

        sem_post(&mutex);
        sem_post(&empty);
    }

    pthread_exit(NULL);
}
