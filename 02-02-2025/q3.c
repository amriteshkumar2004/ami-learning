/*3. Multi-threaded Odd & Even Number Printing */
#include <stdio.h>
#include <pthread.h>

void* print_odd(void* arg) {
    for (int i = 1; i <= 20; i += 2) {
        printf("ODD NUMBER: %d\n", i);
    }
    return NULL;
}

void* print_even(void* arg) {
    for (int i = 2; i <= 20; i += 2) {
        printf("%d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t oddThread, evenThread;
    
    pthread_create(&oddThread, NULL, print_odd, NULL);
    pthread_create(&evenThread, NULL, print_even, NULL);

    pthread_join(oddThread, NULL);
    pthread_join(evenThread, NULL);

    return 0;
}





