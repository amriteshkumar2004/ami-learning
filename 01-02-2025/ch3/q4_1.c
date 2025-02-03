/*Method 2: Using wait() in Parent Process*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child process (PID: %d) exiting...\n", getpid());
        exit(0);
    } else {
        wait(NULL); // Parent waits for the child to terminate
        printf("Child process reaped, avoiding zombie state.\n");
    }

    return 0;
}

