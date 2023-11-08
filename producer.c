// Toby Baker
// OS Proj 1 producer file
#include "header.h"

int main() {
   int item = 1;
   int in = 0;
   int produced_count = 0;

   struct shmbuf *shmptr;

   int shm_fd;

   shm_fd = shm_open(NAME, O_CREAT | O_RDWR, 0600);

   ftruncate(shm_fd, BUF_SIZE);


   shmptr = mmap(0, BUF_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

   while (produced_count < MAX_ITEMS) {
      sem_wait(&shmptr->empty);
      sem_wait(&shmptr->mutex);

      //sprintf(shptr, "%d", item);
      shmptr->buf[in] = item;
      //shptr += strlen(item);
      printf("Produced: %d", item);
      ++item;
      ++produced_count;
      in = (in + 1) % BUFFER_SIZE;

      sem_post(&shmptr->mutex);
      sem_post(&shmptr->full);
   }
   shm_unlink(NAME);
   return 0;
}
/*
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
*/