#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int signal_flag = 0;

void *waiter(void *arg) {
    pthread_mutex_lock(&mutex);
    while (!signal_flag) {
        pthread_cond_wait(&cond, &mutex); // wait for signal
    }
    printf("Thread %ld received the signal.\n", (long)arg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *signaler(void *arg) {
    sleep(1); // delay to ensure waiting thread blocks
    pthread_mutex_lock(&mutex);
    signal_flag = 1;
    pthread_cond_signal(&cond); // send signal
    printf("Thread %ld sent the signal.\n", (long)arg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, waiter, (void *)1);
    pthread_create(&t2, NULL, signaler, (void *)2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
