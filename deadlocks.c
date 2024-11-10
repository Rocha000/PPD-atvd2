#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *thread1(void *arg) {
    printf("Thread 1: Trying to lock mutex1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: mutex1 locked.\n");

    sleep(1); 

    printf("Thread 1: Trying to lock mutex2...\n");
    pthread_mutex_lock(&mutex2); 
    printf("Thread 1: mutex2 locked.\n");

    printf("Thread 1: Working with both mutex1 and mutex2 locked.\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    printf("Thread 1: Released mutex1 and mutex2.\n");
    return NULL;
}

void *thread2(void *arg) {
    printf("Thread 2: Trying to lock mutex2...\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 2: mutex2 locked.\n");

    sleep(1); 

    printf("Thread 2: Trying to lock mutex1...\n");
    pthread_mutex_lock(&mutex1); 
    printf("Thread 2: mutex1 locked.\n");

    printf("Thread 2: Working with both mutex1 and mutex2 locked.\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    printf("Thread 2: Released mutex1 and mutex2.\n");
    return NULL;
}

int main() {
    pthread_t t1, t2;

    
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Program ended.\n");
    return 0;
}
