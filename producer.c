// Toby Baker
// OS Proj 1 producer file
#include "header.h"

int main() {
   pthread_t producerThread;
   int item = 1;
   int in = 0;
   int produced_count = 0;

   struct shmbuf *shmptr;

   int shm_fd;

   shm_fd = shm_open(NAME, O_CREAT | O_RDWR, 0600);
   if (shm_fd == -1)
      errExit("shm_open");

   if (ftruncate(shm_fd, BUF_SIZE) == -1)
      errExit("ftruncate");
   shmptr = mmap(0, BUF_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

   if (sem_init(&shmptr->mutex, 1, 1) == -1)
        errExit("sem_init-mutex");
   if (sem_init(&shmptr->full, 1, 0) == -1)
        errExit("sem_init-full");
   if (sem_init(&shmptr->empty, 1, BUFFER_SIZE) == -1)
        errExit("sem_init-empty");

   pthread_create(&producerThread, NULL, NULL, NULL);
   pthread_join(producerThread, NULL);

   while (produced_count < MAX_ITEMS) {
      sem_wait(&shmptr->empty);
      sem_wait(&shmptr->mutex);

      shmptr->buf[in] = item;
      printf("Produced: %d", item);
      ++item;
      ++produced_count;
      in = (in + 1) % BUFFER_SIZE;

      sem_post(&shmptr->mutex);
      sem_post(&shmptr->full);
   }

   pthread_exit(NULL);
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