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

int main(){
    int item = 1;
    sem_init (&mutex, )

}
