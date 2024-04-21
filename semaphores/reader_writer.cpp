#include <iostream>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, wrt;
int rc = 0;

void* reader(void* arg) {
    while (true) {
        sem_wait(&mutex);
        rc++;
        if (rc == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        std::cout << "Reading object" << std::endl;

        sem_wait(&mutex);
        rc--;
        if (rc == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);
    }
}

void* writer(void* arg) {
    while (true) {
        sem_wait(&wrt);

        std::cout << "Writing into object" << std::endl;

        sem_post(&wrt);
    }
}

int main() {
    pthread_t readerThread[5], writerThread[5];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < 5; ++i) {
        pthread_create(&readerThread[i], NULL, reader, NULL);
        pthread_create(&writerThread[i], NULL, writer, NULL);
    }

    for (int i = 0; i < 5; ++i) {
        pthread_join(readerThread[i], NULL);
        pthread_join(writerThread[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
