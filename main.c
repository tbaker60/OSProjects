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
#include "header.h"

// These need to be put in shared mem
int shm_open(const char *sharedSems, int oflag, mode_t mode);

int main(){
    int fd;
    struct shmbuf *shmp;
    
    fd = shm_open(shmat, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd == -1)
        errExit("shm_open");
    shmp = mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    int item = 1;
    sem_init(&shmp->mutex, 1, 1);
    sem_init(&shmp->full, 1, 0);
    sem_init(&shmp->empty, 1, BUFFER_SIZE);  


    sem_destroy(&shmp->mutex);
    sem_destroy(&shmp->full);
    sem_destroy(&shmp->empty);

    int shm_unlink(const char *sharedSems);
    return 0;
};
