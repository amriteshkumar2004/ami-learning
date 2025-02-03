#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 30

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;  // Mutex for synchronized output

// Function to calculate factorial
long long factorial(int num) {
    long long fact = 1;
    for (int i = 1; i <= num; i++) {
        fact *= i;
    }
    return fact;
}

// Thread function to calculate factorial for odd numbers
void *factorialOdd(void *arg) {
    for (int i = 1; i <= 30; i += 2) {  // Odd numbers: 1, 3, 5, ..., 29
        long long fact = factorial(i);
        
        // Locking before printing to ensure synchronized output
        pthread_mutex_lock(&lock);
        printf("Factorial of %d is %lld\n", i, fact);
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

// Thread function to calculate factorial for even numbers
void *factorialEven(void *arg) {
    for (int i = 2; i <= 30; i += 2) {  // Even numbers: 2, 4, 6, ..., 30
        long long fact = factorial(i);
        
        // Locking before printing to ensure synchronized output
        pthread_mutex_lock(&lock);
        printf("Factorial of %d is %lld\n", i, fact);
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main() {
    // Start time measurement
    clock_t start_time = clock();

    pthread_t oddThread, evenThread;
    
    // Create threads for odd and even numbers
    if (pthread_create(&oddThread, NULL, factorialOdd, NULL) != 0) {
        perror("Failed to create thread for odd numbers");
        exit(1);
    }
    
    if (pthread_create(&evenThread, NULL, factorialEven, NULL) != 0) {
        perror("Failed to create thread for even numbers");
        exit(1);
    }

    // Wait for both threads to complete
    pthread_join(oddThread, NULL);
    pthread_join(evenThread, NULL);

    // End time measurement
    clock_t end_time = clock();
    
    // Calculate the time taken (in seconds)
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    
    // Print the time taken for the execution
    printf("\nTime taken for execution: %f seconds\n", time_taken);

    return 0;
}

