// Create the file q7_2.c (which uses mmap to modify record 43):

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
    int f;
    RECORD *mapped;
    f = open("records.dat", O_RDWR);

    if (f == -1) {
        perror("Error opening file");
        exit(1);
    }

    mapped = (RECORD *)mmap(0, NRECORDS * sizeof(RECORD),
                            PROT_READ | PROT_WRITE, MAP_SHARED, f, 0);

    if (mapped == MAP_FAILED) {
        perror("Error mapping file");
        close(f);
        exit(1);
    }

    mapped[43].integer = 243;
    snprintf(mapped[43].string, sizeof(mapped[43].string), "RECORD-%d", mapped[43].integer);

    msync((void *)mapped, NRECORDS * sizeof(RECORD), MS_ASYNC);

    munmap((void *)mapped, NRECORDS * sizeof(RECORD));
    close(f);

    printf("Record 43 updated using mmap.\n");
    return 0;
}

