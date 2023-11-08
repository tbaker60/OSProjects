// Toby Baker
// OS Project 1 Consumer file
#include "header.h"

// These need stored in shared mem
//int buffer[BUFFER_SIZE];
int main() {
    struct shmbuf shmp;

    void *shptr;

    shmp = shm.open(NAME, O_CREAT | O_RDWR, 0600);

    ftruncate(shm_fd, BUF_SIZE);


    shptr = mmap(0, BUF_SIZE, PROT_WRITE, MAP_SHARED, shmp, 0);
    
    while(consumed_count < MAX_ITEMS) {
        sem_wait(&shmp->full);
        sem_wait(&shmp->empty);

        printf("Consumed: %d", (int *)shptr);
        shptr += strlen((int *)shptr);
        ++consumed_count;

        sem_post(&shmp->mutex);
        sem_post(&eahmp->mpty);
    }
    shm_unlink(NAME);
    return 0;
}

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
