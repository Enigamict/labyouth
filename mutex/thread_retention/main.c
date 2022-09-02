#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int thread_count = 0;

const int loop_max = 100000;

void *ret1(void *arg) {

    int thread_loop = *(int*)arg;

    for (int i = 0; i < thread_loop; i++){
        pthread_mutex_lock(&m);
        thread_count++;
        pthread_mutex_unlock(&m);
    }

    for (int i = 0; i < thread_loop; i++){
        pthread_mutex_lock(&m);
        thread_count--;
        pthread_mutex_unlock(&m);
    }

    printf("%d\n", thread_loop);

    return NULL;

}
int main() {

   pthread_t thread[100];
   int thread_data;
   int main_loop = 100;

   for (int i = 0; i < main_loop; i++) {
        pthread_mutex_lock(&m);
        thread_data = i * 1000;
        pthread_mutex_unlock(&m);
        pthread_create(&thread[i], NULL, ret1, &thread_data);
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
}