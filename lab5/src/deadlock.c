#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* thread1(void* arg) {
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: locked mutex1\n");  
    printf("Thread 1: пытается заблокировать 2ой\n");
    pthread_mutex_lock(&mutex2);  // DEADLOCK
    printf("Thread 1: заблокировал 2ой\n");
    
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    return NULL;
}

void* thread2(void* arg) {
    pthread_mutex_lock(&mutex2);
    printf("Thread 2: locked mutex2\n");
    printf("Thread 2: Пытается заблокировать 1ый\n");
    pthread_mutex_lock(&mutex1);  // DEADLOCK 
    printf("Thread 2: заблокировал 1ый\n");
    
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    
    printf("Запсукаем потоки\n");
    
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    
    // Ждем немного чтобы deadlock успел произойти
    sleep(3);
    
    printf("Программа задедлочилась\n");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    return 0;
}