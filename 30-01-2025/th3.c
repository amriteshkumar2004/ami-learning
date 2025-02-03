#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

static int current = 1;
pthread_mutex_t lock;
pthread_cond_t cond_odd, cond_even;

void *printOdd(void *arg) {
    while (current <= MAX) {
        pthread_mutex_lock(&lock);
        if (current % 2 != 0) {
            printf("Odd: %d\n", current);
            current++;
            pthread_cond_signal(&cond_even);
        } else {
            pthread_cond_wait(&cond_odd, &lock);
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *printEven(void *arg) {
    while (current <= MAX) {
        pthread_mutex_lock(&lock);
        if (current % 2 == 0) {
            printf("Even: %d\n", current);
            current++;
            pthread_cond_signal(&cond_odd);
        } else {
            pthread_cond_wait(&cond_even, &lock);
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t odd_thread, even_thread;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond_odd, NULL);
    pthread_cond_init(&cond_even, NULL);

    pthread_create(&odd_thread, NULL, printOdd, NULL);
    pthread_create(&even_thread, NULL, printEven, NULL);

    pthread_mutex_lock(&lock);
    pthread_cond_signal(&cond_odd);
    pthread_mutex_unlock(&lock);

    pthread_join(odd_thread, NULL);
    pthread_join(even_thread, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond_odd);
    pthread_cond_destroy(&cond_even);

    return 0;
}

