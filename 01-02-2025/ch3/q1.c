/**A1: WAP to Print the Address Causing Segmentation Fault*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <execinfo.h>

void segfault_handler(int sig, siginfo_t *info, void *context) {
    printf("Segmentation fault at address: %p\n", info->si_addr);
    exit(EXIT_FAILURE);
}

int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = segfault_handler;
    sigaction(SIGSEGV, &sa, NULL);

    int *ptr = NULL; // Null pointer dereference
    *ptr = 42; // This will cause a segmentation fault

    return 0;
}

