#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

long long result = 1;
pthread_mutex_t mutex;

void* calculate(void* arg) {
    int thread_id = *(int*)arg;
    int k = ((int*)arg)[1];
    int pnum = ((int*)arg)[2];
    long long mod = *(long long*)((int*)arg + 3);
    
    // Вычисляем диапазон для этого потока
    int numbers_per_thread = k / pnum;
    int remainder = k % pnum;
    
    int start = thread_id * numbers_per_thread + 1;
    int end = (thread_id + 1) * numbers_per_thread;
    
    // Распределяем остаток
    if (thread_id < remainder) {
        start += thread_id;
        end += thread_id + 1;
    } else {
        start += remainder;
        end += remainder;
    }
    
    long long partial = 1;
    for (int i = start; i <= end; i++) {
        partial = (partial * i) % mod;
    }
    
    pthread_mutex_lock(&mutex);
    result = (result * partial) % mod;
    pthread_mutex_unlock(&mutex);
    
    free(arg);
    return NULL;
}

int main(int argc, char* argv[]) {
    int k = 0, pnum = 0;
    long long mod = 0;
    
    // Парсим аргументы
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-k") == 0 && i + 1 < argc) {
            k = atoi(argv[++i]);
        } else if (strncmp(argv[i], "--pnum=", 7) == 0) {
            pnum = atoi(argv[i] + 7);
        } else if (strncmp(argv[i], "--mod=", 6) == 0) {
            mod = atoll(argv[i] + 6);
        }
    }
    
    
    // Если потоков больше чем чисел, ограничиваем
    if (pnum > k) {
        pnum = k;
    }
    
    pthread_t threads[pnum];
    pthread_mutex_init(&mutex, NULL);
    result = 1;  
    
    // Создание потоков
    for (int i = 0; i < pnum; i++) {
        int* data = malloc(5 * sizeof(int));
        data[0] = i;  // thread_id
        data[1] = k;  // k
        data[2] = pnum; // pnum
        *(long long*)(data + 3) = mod; // mod
        
        pthread_create(&threads[i], NULL, calculate, data);
    }
    
    // Ожидание завершения
    for (int i = 0; i < pnum; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Result: %d! mod %lld = %lld\n", k, mod, result);
    
    // Проверка последовательным вычислением
    long long check = 1;
    for (int i = 1; i <= k; i++) {
        check = (check * i) % mod;
    }
    
    pthread_mutex_destroy(&mutex);
    return 0;
}