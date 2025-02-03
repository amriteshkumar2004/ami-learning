#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 30  // Number range

typedef struct {
    int start, end;
    unsigned long long* results;
} ThreadData;

// Function to compute factorial
unsigned long long factorial(int n) {
    unsigned long long fact = 1;
    for (int i = 2; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

// Thread function to compute factorials in a given range
void* computeFactorial(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->start; i <= data->end; ++i) {
        data->results[i - data->start] = factorial(i);
    }
    pthread_exit(NULL);
}

// Function to test execution time with a given number of threads
void testThreads(int numThreads) {
    pthread_t threads[numThreads];
    ThreadData threadData[numThreads];

    int chunkSize = MAX / numThreads;  // Even division
    int remainder = MAX % numThreads;  // Extra work distribution

    clock_t start_time = clock();  // Start time

    int currentStart = 1;
    for (int i = 0; i < numThreads; i++) {
        threadData[i].start = currentStart;
        threadData[i].end = currentStart + chunkSize - 1;

        if (i < remainder) {
            threadData[i].end += 1;  // Distribute remainder work
        }

        int rangeSize = threadData[i].end - threadData[i].start + 1;
        threadData[i].results = (unsigned long long*)malloc(rangeSize * sizeof(unsigned long long));
        if (!threadData[i].results) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        pthread_create(&threads[i], NULL, computeFactorial, (void*)&threadData[i]);

        currentStart = threadData[i].end + 1;
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock();  // Stop time
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Threads: %d, Execution Time: %f seconds\n", numThreads, time_taken);

    for (int i = 0; i < numThreads; i++) {
        free(threadData[i].results);
    }
}

int main() {
    printf("Comparing factorial computation with different thread configurations:\n");

    int threadConfigs[] = {1, 2, 3, 5, 10, 15, 30};  
    int numConfigs = sizeof(threadConfigs) / sizeof(threadConfigs[0]);

    for (int i = 0; i < numConfigs; i++) {
        printf("\nUsing %d threads:\n", threadConfigs[i]);
        testThreads(threadConfigs[i]);
    }

    return 0;
}

