// Toby Baker
// OS Proj 1 Producer-Consumer problem header file
//
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
#include <unistd.h>

// Shared mem setup
///////////////////////////
#define errExit(msg)    do {perror(msg); exit(EXIT_FAILURE);} while (0);
#define BUF_SIZE 1024   /* Maximum size for exchanged string */
#define MAX_ITEMS 20
#define BUFFER_SIZE 5
#define NAME "OS1"

// Shared mem struct definition
struct shmbuf {
    sem_t  mutex;            // POSIX mutex semaphore 
    sem_t  full;             // POSIX full semaphore
    sem_t  empty;            // POSIX empty semaphore
    size_t cnt;             /* Number of bytes used in 'buf' */
    int   buf[BUF_SIZE];    /* Data being transferred */
};
