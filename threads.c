#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // Include this header for the sleep function

// Function to be executed by the thread
void *thread_function(void *arg) {
    int thread_num = *((int *)arg);
    printf("Thread %d started\n", thread_num);
    // Perform some task
    // For demonstration, sleep for 1 second
    sleep(1);
    printf("Thread %d finished\n", thread_num);
    // Exit the thread
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int thread1_num = 1;
    int thread2_num = 2;
    
    // Create thread 1
    if (pthread_create(&thread1, NULL, thread_function, (void *)&thread1_num) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    
    // Create thread 2
    if (pthread_create(&thread2, NULL, thread_function, (void *)&thread2_num) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    
    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("All threads finished\n");
    
    return 0;
}