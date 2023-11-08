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
#include "producer.h"
#include "consumer.h"

// These need to be put in shared mem
int shm_open(const char *sharedSems, int oflag, mode_t mode);

#define errExit(msg)    do {perror(msg); exit(EXIT_FAILURE);} while (0);

#define BUF_SIZE 1024   /* Maximum size for exchanged string */

/* Define a structure that will be imposed on the shared
    memory object */

struct shmbuf {
    sem_t  mutex;            // POSIX mutex semaphore 
    sem_t  full;             // POSIX full semaphore
    sem_t  empty;            // POSIX empty semaphore
    size_t cnt;             /* Number of bytes used in 'buf' */
    int   buf[BUF_SIZE];    /* Data being transferred */
};

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
