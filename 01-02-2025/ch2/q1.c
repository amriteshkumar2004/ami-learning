/* A1: Print the factorial of a given number using multithreads */

#include <stdio.h>
#include <pthread.h>

long long factorial = 1;
int num;
pthread_mutex_t lock;

void *calculate_factorial(void *arg) {
    pthread_mutex_lock(&lock);
    for (int i = 1; i <= num; i++) {
        factorial *= i;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    printf("Enter a number: ");
    scanf("%d", &num);
    
    pthread_t thread;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&thread, NULL, calculate_factorial, NULL);
    pthread_join(thread, NULL);
    pthread_mutex_destroy(&lock);
    
    printf("Factorial of %d is %lld\n", num, factorial);
    return 0;
}

