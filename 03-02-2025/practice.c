/*Spinlock usage
  Why file descriptors should be closed
  What happens when reading from fd[1] (write end of a pipe) */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>

pthread_spinlock_t spinlock;  

void* spinlock_example(void* arg) {
    printf("Thread trying to acquire spinlock...\n");
    pthread_spin_lock(&spinlock);  
    printf("Thread acquired spinlock, holding for 2 seconds...\n");
    sleep(2);
    pthread_spin_unlock(&spinlock);  
    printf("Thread released spinlock.\n");
    return NULL;
}

void file_descriptor_example() {
    int fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("File opened with fd: %d\n", fd);
    close(fd); 
    printf("File descriptor closed.\n");

    if (write(fd, "Hello", 5) == -1) {
        perror("Attempt to write after closing FD");  
    }
}

void pipe_example() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    printf("Pipe created: fd[0] = %d (read), fd[1] = %d (write)\n", fd[0], fd[1]);

    char buffer[100];

    // Trying to read from fd[1] (incorrect usage)
    ssize_t bytesRead = read(fd[1], buffer, sizeof(buffer));

    if (bytesRead == -1) {
        perror("Read from write-end of pipe");
    } else {
        printf("Read %zd bytes from fd[1]: %s\n", bytesRead, buffer);
    }

    close(fd[0]);
    close(fd[1]);
}

int main() {
    pthread_t thread;

    // 1. Spinlock Example
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
    pthread_create(&thread, NULL, spinlock_example, NULL);
    sleep(1);  // Ensure the first thread acquires the spinlock first

    printf("Main thread trying to acquire spinlock...\n");
    pthread_spin_lock(&spinlock);  // Spinlock forces busy waiting
    printf("Main thread acquired spinlock.\n");
    pthread_spin_unlock(&spinlock);
    pthread_join(thread, NULL);
    pthread_spin_destroy(&spinlock);

    // 2. File Descriptor Example
    file_descriptor_example();

    // 3. Pipe Example
    pipe_example();

    return 0;
}

