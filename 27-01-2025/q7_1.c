// Create the file q7_1.c (which modifies record 43 using traditional file I/O):

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int integer;
    char string[24];
} RECORD;

int main() {
    RECORD record;
    FILE *fp;

    // Open the file for reading and writing
    fp = fopen("records.dat", "r+");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // Move to the 43rd record (zero-indexed, so 43rd is at position 43)
    fseek(fp, 43 * sizeof(record), SEEK_SET);

    // Read the current record
    fread(&record, sizeof(record), 1, fp);

    // Update the integer and string of the 43rd record
    record.integer = 143;
    snprintf(record.string, sizeof(record.string), "RECORD-%d", record.integer);

    // Move back to the same position and write the updated record
    fseek(fp, 43 * sizeof(record), SEEK_SET);
    fwrite(&record, sizeof(record), 1, fp);

    fclose(fp);

    printf("Record 43 updated using traditional file I/O.\n");
    return 0;
}

