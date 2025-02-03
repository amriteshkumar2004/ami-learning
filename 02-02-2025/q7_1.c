#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void reap_zombie(int sig) {
    // Reap all zombie children without blocking
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = reap_zombie;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;  // Ensures syscalls restart & ignores stopped children

    sigaction(SIGCHLD, &sa, NULL);

    if (fork() == 0) {
        printf("Child process running...\n");
        sleep(2);
        printf("Child exiting...\n");
        exit(0);
    } else {
        printf("Parent process running...\n");
        sleep(5);
        printf("Parent exiting...\n");
    }

    return 0;
}
