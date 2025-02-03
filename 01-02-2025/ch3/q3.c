/* A3: WAP to Block Certain Signals from Being Received from Command-Line*/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int sig) {
    printf("Signal %d received but blocked!\n", sig);
}

int main() {
    sigset_t block_set;
    sigemptyset(&block_set);
    sigaddset(&block_set, SIGINT);  // Block Ctrl+C (SIGINT)
    sigaddset(&block_set, SIGTERM); // Block SIGTERM

    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_mask = block_set;
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    printf("Press Ctrl+C or send SIGTERM, but they are blocked.\n");

    while (1) {
        sleep(1);
    }

    return 0;
}

