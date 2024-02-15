#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) { // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) { // Child process
        printf("Child process: PID = %d\n", getpid());
        // Child process logic here
        // For example:
        printf("Child process is executing\n");
        sleep(5); // Simulating some work
        printf("Child process is done\n");
    } else { // Parent process
        printf("Parent process: PID = %d\n", getpid());
        printf("Child process created with PID = %d\n", pid);
        // Parent process logic here
        // For example:
        printf("Parent process is waiting for the child to finish...\n");
        wait(NULL); // Wait for child to terminate
        printf("Parent process is done\n");
    }

    return 0;
}
