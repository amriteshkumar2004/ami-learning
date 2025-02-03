#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigsegv_handler(int signum, siginfo_t* info, void* context) {
    printf("Segmentation Fault at address: %p\n", info->si_addr);
    exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigsegv_handler;
    sigaction(SIGSEGV, &sa, NULL);

    int* p = NULL;
    *p = 10;  // Causes segmentation fault

    return 0;
}
