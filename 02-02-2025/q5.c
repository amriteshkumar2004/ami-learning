#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int sig) {
    printf("ALARM! Wake up!\n");
    sleep(2);  // Snooze for 2 seconds
    printf("Snooze over! Time to wake up.\n");
}

int main() {
    signal(SIGALRM, alarm_handler);
    printf("Setting alarm for 5 seconds...\n");
    alarm(5);
    pause();  // Wait for signal
    return 0;
}
