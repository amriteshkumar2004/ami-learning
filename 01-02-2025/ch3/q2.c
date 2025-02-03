/* A2: WAP to Implement Alarm with Snooze for Given Time and Date Using SIGALRM */
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void alarm_handler(int sig) {
    printf("Alarm ringing!\n");
    printf("Press 's' to snooze or any other key to stop: ");

    char choice;
    scanf(" %c", &choice);

    if (choice == 's') {
        printf("Snoozing for 10 seconds...\n");
        alarm(10);
    } else {
        printf("Alarm stopped.\n");
        exit(0);
    }
}

int main() {
    int seconds;
    printf("Set alarm time in seconds: ");
    scanf("%d", &seconds);

    signal(SIGALRM, alarm_handler);
    alarm(seconds);

    while (1) {
        pause(); // Wait for signal
    }

    return 0;
}

