/* A4: Create Three Child Processes from the Same Parent */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("Parent process (PID: %d)\n", getpid());
    fflush(stdout); // Ensure immediate printing

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid < 0) { // Fork failure
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Child process
            printf("Child %d (PID: %d, Parent PID: %d)\n", i + 1, getpid(), getppid());
            fflush(stdout);
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < 3; i++) {
        int status;
        pid_t wpid = wait(&status);

        if (wpid == -1) { // Error in wait()
            perror("wait failed");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("Child process (PID: %d) exited with status %d.\n", wpid, WEXITSTATUS(status));
        } else {
            printf("Child process (PID: %d) terminated abnormally.\n", wpid);
        }
    }

    return EXIT_SUCCESS;
}

