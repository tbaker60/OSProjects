// Toby Baker
// OS Project 1 Consumer file
#include "header.h"

int main() {
    // declaring consumer thread, fd, and shared mem pointer for consumer process
    pthread_t consumerThread;
    struct shmbuf *shmptr;
    int shm_fd;

    // initializing vars needed for consumer
    int consumed_count = 0;
    int out = 0;

    // setting fd and opening shared mem at NAME OS1
    //  plus error checking
    shm_fd = shm_open(NAME, O_CREAT | O_RDWR, 0600);
    if (shm_fd == -1)
      errExit("shm_open");
    // setting shared mem ptr for consumer use by memory map
    shmptr = mmap(0, BUF_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    // running checks on sems to make sure there are no errors
    // would apply more if the shared mem location was dependent on user input
    if (sem_init(&shmptr->mutex, 1, 1) == -1)
        errExit("sem_init-mutex");
    if (sem_init(&shmptr->full, 1, 0) == -1)
        errExit("sem_init-full");
    if (sem_init(&shmptr->empty, 1, BUFFER_SIZE) == -1)
        errExit("sem_init-empty");

    // setting up threads for consumer process
    pthread_create(&consumerThread, NULL, NULL, NULL);
    pthread_join(consumerThread, NULL);

    while(consumed_count < MAX_ITEMS) {
        // putting sems on hold for consumption
        sem_wait(&shmptr->full);
        sem_wait(&shmptr->empty);

        // setting item to current index most recently produced
        int item = shmptr->buf[out];
        printf("Consumed: %d", item);
        // incrementing out index and how many items have been consumed
        out = (out + 1) % BUFFER_SIZE;
        ++consumed_count;

        // freeing sems back up
        sem_post(&shmptr->mutex);
        sem_post(&shmptr->empty);
    }

    // exiting thread and unlinking shared mem
    pthread_exit(NULL);
    shm_unlink(NAME);
    return 0;
}


/*
// old consumer function
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