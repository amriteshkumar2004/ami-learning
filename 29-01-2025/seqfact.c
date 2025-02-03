#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to calculate factorial
long long factorial(int num) {
    long long fact = 1;
    for (int i = 1; i <= num; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    // Start time measurement
    clock_t start_time = clock();

    // Calculate factorial for odd numbers from 1 to 29
    printf("Factorial of odd numbers:\n");
    for (int i = 1; i <= 30; i += 2) {  // Odd numbers: 1, 3, 5, ..., 29
        printf("Factorial of %d is %lld\n", i, factorial(i));
    }

    // Calculate factorial for even numbers from 2 to 30
    printf("\nFactorial of even numbers:\n");
    for (int i = 2; i <= 30; i += 2) {  // Even numbers: 2, 4, 6, ..., 30
        printf("Factorial of %d is %lld\n", i, factorial(i));
    }

    // End time measurement
    clock_t end_time = clock();
    
    // Calculate the time taken (in seconds)
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    
    // Print the time taken for the execution
    printf("\nTime taken for execution: %f seconds\n", time_taken);

    return 0;
}


