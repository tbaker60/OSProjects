// Toby Baker
// OS Project 1 Consumer file



// These need stored in shared mem
//int buffer[BUFFER_SIZE];

extern struct shmbuf *shmp;

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
