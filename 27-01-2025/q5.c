#include <stdio.h>
#include <stdlib.h>

int main() {
    int c;
    FILE *in, *out;

    // Open the input file in read mode
    in = fopen("file.in", "r");
    if (in == NULL) {
        perror("Error opening input file");
        exit(1);
    }

    // Open the output file in write mode
    out = fopen("file.out", "w");
    if (out == NULL) {
        perror("Error opening output file");
        fclose(in);  // Close the input file before exiting
        exit(1);
    }

    // Copy the content from input file to output file character by character
    while ((c = fgetc(in)) != EOF) {
        fputc(c, out);
    }

    // Close both files
    fclose(in);
    fclose(out);

    return 0;
}

