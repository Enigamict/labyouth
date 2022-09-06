#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int thread_count = 0;
int thread_index = 0;
int thread_loop[100];

void *ret1() {

    #ifdef early

    pthread_mutex_lock(&m);
    int thread_loop_cnt = thread_loop[thread_index];
    printf("%d::%d\n", thread_index, thread_loop[thread_index]);
    pthread_mutex_unlock(&m);

    pthread_mutex_lock(&m);
    for (int i = 0; i < thread_loop_cnt; i++) {
        thread_count++;
    }
    pthread_mutex_unlock(&m);

    pthread_mutex_lock(&m);
    for (int i = 0; i < thread_loop_cnt; i++){
        thread_count--;
    }
    printf("%d\n", thread_count);
    pthread_mutex_unlock(&m);

    return NULL;
    #else

    pthread_mutex_lock(&m);
    int thread_loop_cnt = thread_loop[thread_index];
    printf("%d::%d\n", thread_index, thread_loop[thread_index]);
    for (int i = 0; i < thread_loop_cnt; i++) {
        thread_count++;
    }
    for (int i = 0; i < thread_loop_cnt; i++){
        thread_count--;
    }
    printf("%d\n", thread_count);
    pthread_mutex_unlock(&m);
    return NULL;
    #endif


}
int main() {

   pthread_t thread[100];
   const int main_loop = 100;
   clock_t begin = clock();

   for (int i = 0; i < main_loop; i++) {
        pthread_mutex_lock(&m);
        thread_loop[i] = i * 1000;
        thread_index = i;
        pthread_mutex_unlock(&m);
        pthread_create(&thread[i], NULL, ret1, NULL);
   }

   for (int i = 0; i < main_loop; i++) {
        printf("thread ID:%p\n", thread[i]);
   }


   for (int i = 0; i < main_loop; i++) {
        int join;
        join = pthread_join(thread[i], NULL);
        printf("join:%d\n", join);
   }


   printf("thread_cnt:%d\n", thread_count);
   clock_t end = clock();

   printf("result: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);

   pthread_mutex_destroy(&m);
}