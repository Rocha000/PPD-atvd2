#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int num_readers = 0;
int data = 0; // shared resource

void *reader(void *arg) {
    pthread_mutex_lock(&mutex);
    num_readers++;
    pthread_mutex_unlock(&mutex);

    printf("Reader %ld reading data: %d\n", (long)arg, data);

    pthread_mutex_lock(&mutex);
    num_readers--;
    if (num_readers == 0) pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *writer(void *arg) {
    pthread_mutex_lock(&mutex);
    while (num_readers > 0)
        pthread_cond_wait(&cond, &mutex);

    data = rand() % 100; // update resource
    printf("Writer %ld wrote data: %d\n", (long)arg, data);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t readers[5], writers[5];
    for (long i = 0; i < 5; i++) {
        pthread_create(&writers[i], NULL, writer, (void *)i);
        pthread_create(&readers[i], NULL, reader, (void *)i);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }
    return 0;
}
