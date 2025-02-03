/* 1. Multi-threaded Factorial Calculation */
#include <stdio.h>
#include <pthread.h>

typedef struct {
    int num;
    unsigned long long result;
} FactorialArgs;

void* factorial(void* arg) {
    FactorialArgs* data = (FactorialArgs*)arg;
    int n = data->num;
    data->result = 1;
    for (int i = 1; i <= n; i++) {
        data->result *= i;
    }
    return NULL;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    pthread_t thread;
    FactorialArgs args = {num, 1};

    pthread_create(&thread, NULL, factorial, &args);
    pthread_join(thread, NULL);

    printf("Factorial of %d is %llu\n", num, args.result);
    return 0;
}

