/*2. Multi-threaded Matrix Multiplication */
#include <stdio.h>
#include <pthread.h>

#define ROWS 3
#define COLS 3

int M1[ROWS][COLS] = {{1, 2, 3}, {1, 1, 1}, {2, 2, 2}};
int M2[ROWS][COLS] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
int result[ROWS][COLS];

typedef struct {
    int row;
} ThreadArgs;

void* multiply_row(void* arg) {
    ThreadArgs* data = (ThreadArgs*)arg;
    int row = data->row;
    for (int j = 0; j < COLS; j++) {
        result[row][j] = 0;
        for (int k = 0; k < COLS; k++) {
            result[row][j] += M1[row][k] * M2[k][j];
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[ROWS];
    ThreadArgs args[ROWS];

    for (int i = 0; i < ROWS; i++) {
        args[i].row = i;
        pthread_create(&threads[i], NULL, multiply_row, &args[i]);
    }

    for (int i = 0; i < ROWS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Resultant Matrix:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}

