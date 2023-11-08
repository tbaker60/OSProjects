// Toby Baker
// OS Proj 1 producer file

// MAKE SURE YOU ADD COMMENTS TO THIS CODE
#define BUFFER_SIZE 5
#define MAX_ITEMS 20

// These need stored in shared mem
//int buffer[BUFFER_SIZE];
int in = 0;
//int out = 0;
int produced_count = 0;
//int consumed_count = 0;
extern struct shmbuf *shmp;


void* producer(struct shmbuf *shmp) {
   int item = 1;

   while (produced_count < MAX_ITEMS) {
      sem_wait(&shmp->empty);
      sem_wait(&shmp->mutex);

      &shmp->buf[in] = item;
      printf("Produced: %d", item);
      item++;
      in = (in + 1) % BUFFER_SIZE;

      produced_count++;

      sem_post(&shmp->mutex);
      sem_post(&shmp->full);
   }

   pthread_exit(NULL);
}
