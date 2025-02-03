/* A3: Multiply two matrices using multiple threads */
#include <stdio.h>
#include <pthread.h>
#define N 2
#define M 2
int A[N][M] = {{1, 2}, {3, 4}};
int B[N][M] = {{5, 6}, {7, 8}};
int C[N][M];
void *multiply(void *arg) {
    int i = *(int *)arg;
    for (int j = 0; j < M; j++) {
        C[i][j] = 0;
        for (int k = 0; k < M; k++) {
            C[i][j] += A[i][k] * B[k][j];
        }
    }
    return NULL;
}
int main() {
    pthread_t threads[N];
    int indices[N];
    for (int i = 0; i < N; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL, multiply, &indices[i]);
    }
    for (int i = 0; i < N; i++) pthread_join(threads[i], NULL);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) printf("%d ", C[i][j]);
        printf("\n");
    }
    return 0;
}
