// Toby Baker
// OS Project 1 Consumer file
#define BUFFER_SIZE 5
#define MAX_ITEMS 20


// These need stored in shared mem
//int buffer[BUFFER_SIZE];
//int in = 0;
int out = 0;
//int produced_count = 0;
int consumed_count = 0;

void* consumer(struct shmbuf *shmp) {
    while(consumed_count < MAX_ITEMS) {
        sem_wait(&shmp->full);
        sem_wait(&shmp->empty);

        int item = &shmp->buf[out];
        printf("Consumed: %d", item);
        out = (out + 1) % BUFFER_SIZE;
        ++consumed_count;

        sem_post(&shmp->mutex);
        sem_post(&eahmp->mpty);
    }

    pthread_exit(NULL);
}
