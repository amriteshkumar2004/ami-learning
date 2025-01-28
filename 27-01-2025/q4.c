#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char block[1024];  // Buffer for reading and writing 1KB blocks
    int in, out;       // File descriptors for input and output files
    int nread;

    // Open the input file in read-only mode
    in = open("file.in", O_RDONLY);
    if (in < 0) {
        perror("Error opening input file");
        exit(1);
    }

    // Open the output file in write-only mode, create it if it doesn't exist, and set permissions
    out = open("file.out", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (out < 0) {
        perror("Error opening/creating output file");
        close(in);
        exit(1);
    }

    // Read and write in 1KB blocks
    while ((nread = read(in, block, sizeof(block))) > 0) {
        write(out, block, nread);
    }

    // Close both files
    close(in);
    close(out);

    return 0;
}

