#include <stdio.h>

int main() {
    // fseek example
    FILE *file = fopen("example.txt", "r+");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 5, SEEK_SET); // Move file pointer to the 5th byte
    char ch = fgetc(file);
    printf("Character at position 5: %c\n", ch);
    fclose(file);

    // fgets example
    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char buffer[100];
    if (fgets(buffer, sizeof(buffer), file)) {
        printf("First line of the file: %s\n", buffer);
    } else {
        perror("Error reading file");
    }
    fclose(file);

    // getc and getchar example
    printf("Enter a character: ");
    int c = getchar(); // Read a character from stdin
    printf("You entered: %c\n", c);

    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    c = getc(file); // Read a character from the file
    printf("Character from file: %c\n", c);
    fclose(file);

    // printf, fprintf, and sprintf examples
    printf("This is printed using printf\n");

    file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "This is printed using fprintf\n");
    fclose(file);

    char str[50];
    sprintf(str, "Formatted string with number: %d", 100);
    printf("Formatted string: %s\n", str);

    return 0;
}

