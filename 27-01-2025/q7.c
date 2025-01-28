// Create the file q7.c (which writes records to records.dat):

#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct {
    int integer;
    char string[24];
} RECORD;

#define NRECORDS (100)

int main() {
    RECORD record;
    int i;
    FILE *fp;

    fp = fopen("records.dat", "w+");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    for (i = 0; i < NRECORDS; i++) {
        record.integer = i;
        snprintf(record.string, sizeof(record.string), "RECORD-%d", i);
        fwrite(&record, sizeof(record), 1, fp);
    }

    fclose(fp);

    printf("Records written to file.\n");
    return 0;
}

