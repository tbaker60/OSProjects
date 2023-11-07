// Toby Baker
// OS Proj 1 producer file
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 20

// MAKE SURE YOU ADD COMMENTS TO THIS CODE

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int produced_count = 0;
int consumed_count = 0;

sem_t mutex;
sem_t full;
sem_t empty;

void* producer(void* arg) {
   int item = 1;

   while (produced_count < MAX_ITEMS) {
      sem_wait(&empty);
      sem_wait(&mutex);

      buffer[in] = item;
      printf("Produced: %d", item);
      item++;
      in = (in + 1) % BUFFER_SIZE;

      produced_count++;

      sem_post(&mutex);
      sem_post(&full);
   }

   pthread_exit(NULL);
}

int main(){
    int item = 1;
    sem_init(&mutex, 1, 1);
    sem_init(&full, 1, 0);
    sem_init(&empty, 1, BUFFER_SIZE);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(&producerThread, NULL);
    pthread_join(&consumerThread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
