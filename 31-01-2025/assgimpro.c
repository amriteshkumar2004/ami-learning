#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 50

int main(int argc, char *argv[])
{
    int pfd[2];
    char buf[BUF_SIZE] = {};
    ssize_t numRead;

    /* Check for correct usage */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <message>\n", argv[0]);
        exit(1);
    }

    /* Create the pipe */
    if (pipe(pfd) == -1) {
        perror("pipe");
        exit(1);
    }

    switch (fork()) {
        case -1:
            perror("fork");
            exit(1);

        case 0: /* Child process */
            if (close(pfd[1]) == -1) {
                perror("close write-end in child");
                exit(1);
            }

            for (;;) {
                memset(buf, 0, BUF_SIZE); // Clear buffer before reading
                numRead = read(pfd[0], buf, BUF_SIZE - 1);
                
                if (numRead == -1) {
                    perror("read");
                    exit(1);
                }
                
                if (numRead == 0) {
                    printf("\nChild: Parent closed write end\n");
                    break;
                }

                buf[numRead] = '\0'; // Null-terminate string
                printf("\nData received in child process: (%s)\n", buf);
            }

            if (close(pfd[0]) == -1) {
                perror("close read-end in child");
                exit(1);
            }
            exit(0);

        default: /* Parent process */
            if (close(pfd[0]) == -1) {
                perror("close read-end in parent");
                exit(1);
            }

            printf("\nParent: Sending user input string to child process - (%s)\n", argv[1]);
            if (write(pfd[1], argv[1], strlen(argv[1])) == -1) {
                perror("write");
                exit(1);
            }

            sleep(2);

            if (close(pfd[1]) == -1) {
                perror("close write-end in parent");
                exit(1);
            }

            printf("\nParent: Closed write end\n");
            wait(NULL); // Wait for child process to finish
            exit(0);
    }
}

