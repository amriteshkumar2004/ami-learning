// A file copy program
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    char c;          // Buffer to store a single character
    int in, out;     // File descriptors for input and output files

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

    // Read character by character from input file and write to output file
    while (read(in, &c, 1) == 1) {
        write(out, &c, 1);
    }

    // Close both files
    close(in);
    close(out);

    return 0;
}

