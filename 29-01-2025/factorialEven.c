#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 30

// Function to calculate factorial
void *factorial(void *arg) {
    int num = *(int *)arg;
    long long fact = 1;

    for (int i = 1; i <= num; i++) {
        fact *= i;
    }

    printf("Factorial of %d is %lld\n", num, fact);
    return NULL;
}

int main() {
    pthread_t threads[MAX / 2];  // 15 threads for even numbers
    int numbers[MAX / 2];        // Store even numbers

    int index = 0;
    for (int i = 2; i <= MAX; i += 2) {  // Even numbers: 2, 4, 6, ..., 30
        numbers[index] = i;
        pthread_create(&threads[index], NULL, factorial, &numbers[index]);
        index++;
    }

    // Wait for all threads to complete
    for (int i = 0; i < MAX / 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

