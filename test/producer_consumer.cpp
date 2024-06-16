#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <vector>

using namespace std;

#define BUFFER_SIZE 2
#define NUM_ITEMS 6

sem_t mutex_, empty_, full_;
vector<int> buffer(BUFFER_SIZE);
int in = 0, out = 0;

void* producer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        sem_wait(&empty_);
        sem_wait(&mutex_);

        buffer[in] = i;
        cout << "Produced: " << i << endl;
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex_);
        sem_post(&full_);
        sleep(1);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        sem_wait(&full_);
        sem_wait(&mutex_);

        int item = buffer[out];
        cout << "Consumed: " << item << endl;
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex_);
        sem_post(&empty_);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producerThread, consumerThread;

    sem_init(&mutex_, 0, 1);
    sem_init(&empty_, 0, BUFFER_SIZE);
    sem_init(&full_, 0, 0);

    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    sem_destroy(&mutex_);
    sem_destroy(&empty_);
    sem_destroy(&full_);
    return 0;
}
