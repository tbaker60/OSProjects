// Toby Baker
// OS Project 1 main file
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <ctype.h>
#include "header.h"

int shm_open(const char *sharedMem, int oflag, mode_t mode);

int main(int argc, char *argv[]){
    pthread_t producerThread, consumerThread;

    int    fd;
    char   *shmpath = argv[1];
    struct shmbuf *shmp;
    
    fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd == -1)
        errExit("shm_open");
    if (ftruncate(fd, sizeof(struct shmbuf)) == -1)
        errExit("ftruncate");
    shmp = mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shmp == MAP_FAILED)
        errExit("mmap");
    
    if (sem_init(&shmp->mutex, 1, 1) == -1)
        errExit("sem_init-mutex");
    if (sem_init(&shmp->full, 1, 0) == -1)
        errExit("sem_init-full");
    if (sem_init(&shmp->empty, 1, BUFFER_SIZE) == -1)
        errExit("sem_init-empty");

    pthread_create(&producerThread, NULL, &shmp, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    if (sem_wait(&shmp->mutex) == -1)
        errExit("sem_wait");
    
    for (size_t j = 0; j < shmp->cnt; j++)
        shmp->buf[j] = toupper((unsigned char) shmp->buf[j]);
    
    if (sem_post(&shmp->full) == -1 || sem_post(&shmp->empty) == -1)
        errExit("sem_post");

    sem_destroy(&shmp->mutex);
    sem_destroy(&shmp->full);
    sem_destroy(&shmp->empty);

    shm_unlink(shmpath);
    exit(EXIT_SUCCESS);
}
