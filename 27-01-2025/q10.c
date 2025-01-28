#include <stdio.h>

int main() {
    // scanf example
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);
    printf("You entered: %d\n", num);

    // fscanf example
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fscanf(file, "%d", &num); // Read an integer from the file
    printf("Read integer from file: %d\n", num);
    fclose(file);

    // sscanf example
    char str[] = "123 456 789";
    int a, b, c;
    sscanf(str, "%d %d %d", &a, &b, &c); // Parse integers from string
    printf("Parsed integers: %d, %d, %d\n", a, b, c);

    return 0;
}

