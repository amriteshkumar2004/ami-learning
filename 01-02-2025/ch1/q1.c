/* A1: Implement a cp (copy) command with -p option */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 4096

void copy_with_permissions(const char *source, const char *destination) {
    int src_fd, dest_fd;
    struct stat file_stat;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    // Open source file
    if ((src_fd = open(source, O_RDONLY)) == -1) {
        fprintf(stderr, "Error opening source file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Get source file metadata
    if (fstat(src_fd, &file_stat) == -1) {
        perror("Error getting file status");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    // Open destination file with same permissions
    if ((dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, file_stat.st_mode)) == -1) {
        fprintf(stderr, "Error opening destination file: %s\n", strerror(errno));
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    // Copy contents
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        if ((bytes_written = write(dest_fd, buffer, bytes_read)) != bytes_read) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    // Error handling for read
    if (bytes_read == -1) {
        perror("Error reading source file");
    }

    close(src_fd);
    close(dest_fd);
    printf("File copied successfully with permissions preserved.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return EXIT_FAILURE;
    }
    copy_with_permissions(argv[1], argv[2]);
    return EXIT_SUCCESS;
}

