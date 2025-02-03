/*A3: Create a Child Process to Execute a Command Passed as Argument*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t pid = fork();

    if (pid < 0) { // Check for fork failure
        perror("fork failed");
        return EXIT_FAILURE;
    }

    if (pid == 0) { // Child process
        execvp(argv[1], &argv[1]); // Execute command
        perror("execvp failed"); // Print error if exec fails
        exit(EXIT_FAILURE);
    } else { // Parent process
        int status;
        if (wait(&status) == -1) { // Wait for child and handle errors
            perror("wait failed");
            return EXIT_FAILURE;
        }

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d.\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally.\n");
        }
    }

    return EXIT_SUCCESS;
}

