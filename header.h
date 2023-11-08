// Toby Baker
// OS Proj 1 Producer-Consumer problem header file
//


// Shared mem setup
///////////////////////////
#define errExit(msg)    do {perror(msg); exit(EXIT_FAILURE);} while (0);
#define BUF_SIZE 1024   /* Maximum size for exchanged string */
#define MAX_ITEMS 20
#define BUFFER_SIZE 5

// Shared mem struct definition
struct shmbuf {
    sem_t  mutex;            // POSIX mutex semaphore 
    sem_t  full;             // POSIX full semaphore
    sem_t  empty;            // POSIX empty semaphore
    size_t cnt;             /* Number of bytes used in 'buf' */
    int   buf[BUF_SIZE];    /* Data being transferred */
};

// Producer/consumer variables
///////////////////////////////
int in = 0;
int out = 0;
int produced_count = 0;
int consumed_count = 0;

// Producer function
//////////////////////////
void* producer(struct shmbuf *shmp) {
   int item = 1;

   while (produced_count < MAX_ITEMS) {
      sem_wait(&shmp->empty);
      sem_wait(&shmp->mutex);

      shmp->buf[in] = item;
      printf("Produced: %d", item);
      item++;
      in = (in + 1) % BUFFER_SIZE;

      produced_count++;

      sem_post(&shmp->mutex);
      sem_post(&shmp->full);
   }

   pthread_exit(NULL);
}


// Consumer function
/////////////////////////
void* consumer(struct shmbuf *shmp) {
    while(consumed_count < MAX_ITEMS) {
        sem_wait(&shmp->full);
        sem_wait(&shmp->empty);

        int item = shmp->buf[out];
        printf("Consumed: %d", item);
        out = (out + 1) % BUFFER_SIZE;
        ++consumed_count;

        sem_post(&shmp->mutex);
        sem_post(&shmp->empty);
    }

    pthread_exit(NULL);
}