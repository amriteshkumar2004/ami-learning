#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void handle_sigchld(int sig) {
    // Use waitpid with WNOHANG to avoid blocking
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigchld;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;  // Restart interrupted syscalls

    sigaction(SIGCHLD, &sa, NULL);

    if (fork() == 0) {
        printf("Child process running...\n");
        sleep(2);
        printf("Child exiting...\n");
        exit(0);
    } else {
        printf("Parent waiting...\n");
        sleep(5);
        printf("Parent exiting...\n");
    }

    return 0;
}
