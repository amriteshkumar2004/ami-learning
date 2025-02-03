/*A3: Program to understand dup and dup2 system calls*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Duplicate file descriptor
    int copy_fd = dup(fd);
    if (copy_fd < 0) {
        perror("Error using dup");
        close(fd);
        return EXIT_FAILURE;
    }

    // Duplicate file descriptor to a specific descriptor number
    int copy_fd2 = dup2(fd, 10);
    if (copy_fd2 < 0) {
        perror("Error using dup2");
        close(fd);
        close(copy_fd);
        return EXIT_FAILURE;
    
    }

    printf("Original FD: %d\n", fd);
    printf("Duplicate FD (dup): %d\n", copy_fd);
    printf("Duplicate FD (dup2): %d\n", copy_fd2);

    // Write using duplicate file descriptors
    write(copy_fd, "Hello using dup\n", 17);
    write(copy_fd2, "Hello using dup2\n", 18);

    // Close file descriptors
    close(fd);
    close(copy_fd);
    close(copy_fd2);

    return EXIT_SUCCESS;
}

