/* A1: Create a Scenario to Make a Zombie Process Become an Orphan & Print Status */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        printf("Child process (PID: %d) exiting...\n", getpid());
        exit(0);
    } else if (pid > 0) { // Parent process
        printf("Parent process (PID: %d) created child (PID: %d)\n", getpid(), pid);
        sleep(2); // Give time for child to terminate, making it a zombie

        char cmd[50];
        sprintf(cmd, "ps -eo pid,ppid,stat,cmd | grep %d", pid);
        system(cmd); // Show process status

        printf("Parent exiting, making the zombie an orphan...\n");
    } else {
        perror("fork");
    }

    return 0;
}

