// Toby Baker
// OS Project 1 main file


int main(){
    pthread_t producerThread, consumerThread;
    int item = 1;
    sem_init(&mutex, 1, 1);
    sem_init(&full, 1, 0);
    sem_init(&empty, 1, BUFFER_SIZE);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(&producerThread, NULL);
    pthread_join(&consumerThread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
