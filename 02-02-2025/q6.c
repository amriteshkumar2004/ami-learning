#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught signal %d\n", sig);
}

int main() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);  // Block Ctrl+C
    sigaddset(&set, SIGTERM);

    sigprocmask(SIG_BLOCK, &set, NULL);

    printf("Signals SIGINT and SIGTERM are blocked. Press Ctrl+C to test.\n");
    sleep(10);

    sigprocmask(SIG_UNBLOCK, &set, NULL);
    printf("Signals are now unblocked.\n");

    return 0;
}
