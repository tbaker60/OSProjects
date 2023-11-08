// Toby Baker
// OS Project 1 Consumer file
#include "header.h"

int main() {
    pthread consumerThread;
    struct shmbuf *shmptr;

    int shm_fd;

    shm_fd = shm_open(NAME, O_CREAT | O_RDWR, 0600);

    shmptr = mmap(0, BUF_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    if (sem_init(&shmp->mutex, 1, 1) == -1)
        errExit("sem_init-mutex");
    if (sem_init(&shmp->full, 1, 0) == -1)
        errExit("sem_init-full");
    if (sem_init(&shmp->empty, 1, BUFFER_SIZE) == -1)
        errExit("sem_init-empty");

    pthread_create(&consumerThread, NULL, consumer, NULL);
    pthread_join(consumerThread, NULL);

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

    pthread_exit(NULL);
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