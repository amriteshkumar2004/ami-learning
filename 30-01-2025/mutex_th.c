#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int glob = 0;  // Shared variable
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;  // Mutex initialization

void *threadFunc(void *arg) {
    int loc, j;
    int loop = 10000;

    for (j = 0; j < loop; j++) {
        pthread_mutex_lock(&lock);  // Lock before accessing shared data
        loc = glob;
        loc++;
        glob = loc;
        pthread_mutex_unlock(&lock);  // Unlock after modifying shared data
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int s;

    // No need to explicitly initialize the mutex because of PTHREAD_MUTEX_INITIALIZER
    // pthread_mutex_init(&lock, NULL); // Mutex initialization is done here already

    s = pthread_create(&t1, NULL, threadFunc, NULL);
    if (s != 0) perror("pthread_create");

    s = pthread_create(&t2, NULL, threadFunc, NULL);
    if (s != 0) perror("pthread_create");

    s = pthread_join(t1, NULL);
    if (s != 0) perror("pthread_join");

    s = pthread_join(t2, NULL);
    if (s != 0) perror("pthread_join");

    printf("Final value of glob = %d\n", glob);

    pthread_mutex_destroy(&lock);  // Destroy the mutex

    return 0;
}

