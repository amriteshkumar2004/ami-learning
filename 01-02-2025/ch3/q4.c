/*A4: WAP to Avoid a Child Becoming Zombie Using Signal Handlers (1st Method)*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void sigchld_handler(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0); // Reap all child processes
}

int main() {
    signal(SIGCHLD, sigchld_handler);

    if (fork() == 0) {
        printf("Child process (PID: %d) exiting...\n", getpid());
        exit(0);
    }

    printf("Parent process (PID: %d) waiting...\n", getpid());

    while (1) {
        sleep(1);
    }

    return 0;
}

