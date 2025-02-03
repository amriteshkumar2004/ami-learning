/*A2: Implement wc (word count) command with -l -w -c options */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

void word_count(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int lines = 0, words = 0, chars = 0;
    char ch, prev = '\0';

    while ((ch = fgetc(file)) != EOF) {
        chars++;
        if (ch == '\n') lines++;
        if (isspace(ch) && !isspace(prev)) words++;
        prev = ch;
    }

    fclose(file);
    printf("Lines: %d\nWords: %d\nChars: %d\n", lines, words, chars);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    word_count(argv[1]);
    return EXIT_SUCCESS;
}

