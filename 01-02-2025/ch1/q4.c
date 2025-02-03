/*A4: Program to understand advanced file control system calls */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("testfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    printf("File 'testfile.txt' opened with file descriptor: %d\n", fd);

    int flags = fcntl(fd, F_GETFL);
    if (flags < 0) {
        perror("fcntl F_GETFL");
        return 1;
    }

    printf("File flags before modification: %d\n", flags);

    flags |= O_APPEND;
    if (fcntl(fd, F_SETFL, flags) < 0) {
        perror("fcntl F_SETFL");
        return 1;
    }

    printf("File flags after adding O_APPEND: %d\n", flags);

    write(fd, "Appending text\n", 15);
    close(fd);

    printf("Data written successfully!\n");

    return 0;
}

