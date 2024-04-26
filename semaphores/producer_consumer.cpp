#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <vector>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

sem_t mutex, empty, full;
std::vector<int> buffer(BUFFER_SIZE);
int in = 0, out = 0;

void* producer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = i;
        std::cout << "Produced: " << i << std::endl;
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        std::cout << "Consumed: " << item << std::endl;
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);
        sleep(10);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producerThread, consumerThread;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
