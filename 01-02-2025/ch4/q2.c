/*A2: Avoid a Child Becoming a Zombie Without Blocking the Parent*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void handle_sigchld(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0); // Reap all zombie children
}

int main() {
    signal(SIGCHLD, handle_sigchld); // Handle zombie cleanup

    pid_t pid = fork();
    if (pid == 0) { // Child
        printf("Child (PID: %d) exiting...\n", getpid());
        exit(0);
    } else if (pid > 0) { // Parent
        printf("Parent (PID: %d) running without blocking...\n", getpid());
        sleep(5); // Simulating work
    } else {
        perror("fork");
    }

    return 0;
}

