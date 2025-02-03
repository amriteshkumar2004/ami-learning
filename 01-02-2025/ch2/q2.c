/* A2: Sum and maximum of a given array using multiple threads with mutex */
#include <stdio.h>
#include <pthread.h>
#define SIZE 5

int array[SIZE] = {1, 2, 3, 4, 5};
int sum = 0, max = 0;
pthread_mutex_t lock;

void *compute_sum(void *arg) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < SIZE; i++) sum += array[i];
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *compute_max(void *arg) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < SIZE; i++) if (array[i] > max) max = array[i];
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&t1, NULL, compute_sum, NULL);
    pthread_create(&t2, NULL, compute_max, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);
    printf("Sum: %d, Max: %d\n", sum, max);
    return 0;
}

