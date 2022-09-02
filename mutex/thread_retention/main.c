#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int thread_count = 0;

const size_t loop_max = 100000;

void *ret1() {
    for (size_t i = 0; i < loop_max; i++){
        pthread_mutex_lock(&m);
        thread_count++;
        pthread_mutex_unlock(&m);
    }

    for (size_t i = 0; i < loop_max; i++){
        pthread_mutex_lock(&m);
        thread_count--;
        pthread_mutex_unlock(&m);
    }

    return NULL;

}
int main() {

   pthread_t thread[100];

   for (int i = 0; i < 100; i++) {
        pthread_create(&thread[i], NULL, ret1, NULL);
   }

   for (int i = 0; i < 100; i++) {
        printf("thread ID:%p\n", thread[i]);
   }

   for (int i = 0; i < 100; i++) {
        int join;
        join = pthread_join(thread[i], NULL);
        printf("join:%d\n", join);
   }


   printf("thread_cnt:%d\n", thread_count);
}