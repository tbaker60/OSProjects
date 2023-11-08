// Toby Baker
// OS Project 1 Consumer file
#include "header.h"

// These need stored in shared mem
//int buffer[BUFFER_SIZE];
int main() {
    struct shmbuf *shmptr;

    int shm_fd;

    shm_fd = shm_open(NAME, O_CREAT | O_RDWR, 0600);

    shmptr = mmap(0, BUF_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    while(consumed_count < MAX_ITEMS) {
        sem_wait(&shmptr->full);
        sem_wait(&shmptr->empty);

        int item = shmptr->buf[out];
        printf("Consumed: %d", item);
        out = (out + 1) % BUFFER_SIZE;
        ++consumed_count;

        sem_post(&shmptr->mutex);
        sem_post(&shmptr->empty);
    }
    shm_unlink(NAME);
    return 0;
}
/*
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
*/