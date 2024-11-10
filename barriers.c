#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_barrier_t barrier;

void *worker(void *arg) {
    printf("Thread %ld reached the barrier.\n", (long)arg);

    pthread_barrier_wait(&barrier); // synchronization barrier

    printf("Thread %ld passed the barrier.\n", (long)arg);
    return NULL;
}

int main() {
    pthread_t threads[5];
    pthread_barrier_init(&barrier, NULL, 5); // initialize barrier for 5 threads

    for (long i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, worker, (void *)i);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);
    return 0;
}
