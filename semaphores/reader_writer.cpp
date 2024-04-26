#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <unistd.h> // For sleep

using namespace std;

sem_t mutex; // Semaphore to protect the readers count
sem_t wrt;   // Semaphore to ensure exclusive access to writers
int readerCount = 0; // Number of readers accessing the resource
int sharedData = 0;  // Shared resource

void reader(int id) {
    // Reader enters
    sem_wait(&mutex); // Lock mutex
    readerCount++; // Increment reader count
    if (readerCount == 1) {
        sem_wait(&wrt); // First reader locks the writer semaphore
    }
    sem_post(&mutex); // Unlock mutex

    // Reading the shared resource
    cout << "Reader " << id << " reads data: " << sharedData << endl;

    // Reader exits
    sem_wait(&mutex); // Lock mutex
    readerCount--; // Decrement reader count
    if (readerCount == 0) {
        sem_post(&wrt); // Last reader unlocks the writer semaphore
    }
    sem_post(&mutex); // Unlock mutex
}

void writer(int id) {
    // Writer enters
    sem_wait(&wrt); // Lock the writer semaphore

    // Writing to the shared resource
    sharedData = id; // Set data to writer's ID for demonstration
    cout << "Writer " << id << " writes data: " << sharedData << endl;

    // Writer exits
    sem_post(&wrt); // Unlock the writer semaphore
}

int main() {
    const int numReaders = 3; // Number of readers
    const int numWriters = 5; // Number of writers

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    vector<thread> threads;

    // Create reader threads
    for (int i = 1; i <= numReaders; ++i) {
        threads.emplace_back(reader, i);
    }

    // Create writer threads
    for (int i = 1; i <= numWriters; ++i) {
        threads.emplace_back(writer, i);
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    // Clean up semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
