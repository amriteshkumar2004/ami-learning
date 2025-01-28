#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // lseek example
    int fd = open("example.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    printf("Initial file offset: %ld\n", (long)lseek(fd, 0, SEEK_CUR)); // Get current file offset

    // Move file offset 10 bytes from the beginning
    off_t new_offset = lseek(fd, 10, SEEK_SET);
    if (new_offset == -1) {
        perror("Error using lseek");
        close(fd);
        return 1;
    }
    printf("New file offset: %ld\n", (long)new_offset);

    // dup and dup2 example
    int fd_copy = dup(fd); // Create a copy of fd
    if (fd_copy == -1) {
        perror("Error duplicating file descriptor");
        close(fd);
        return 1;
    }

    printf("File descriptor copy created: %d\n", fd_copy);

    int fd_new = open("output.txt", O_WRONLY | O_CREAT, 0644); // New file to redirect
    if (fd_new == -1) {
        perror("Error opening new file");
        close(fd);
        return 1;
    }

    if (dup2(fd_new, fd) == -1) {
        perror("Error redirecting file descriptor");
        close(fd);
        close(fd_new);
        return 1;
    }
    printf("File descriptor %d redirected to %d\n", fd, fd_new);

    close(fd);
    close(fd_copy);
    close(fd_new);

    return 0;
}

