// Toby Baker
// OS Proj 1 producer file

// MAKE SURE YOU ADD COMMENTS TO THIS CODE



void* producer(void* arg) {
   int item = 1;

   while (produced_count < MAX_ITEMS) {
      sem_wait(&empty);
      sem_wait(&mutex);

      buffer[in] = item;
      printf("Produced: %d", item);
      item++;
      in = (in + 1) % BUFFER_SIZE;

      produced_count++;

      sem_post(&mutex);
      sem_post(&full);
   }

   pthread_exit(NULL);
}
