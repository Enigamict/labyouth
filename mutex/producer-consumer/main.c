#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "../../linklist/queue/queue.h"

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

queue *que;

void *thread_push() {

    pthread_mutex_lock(&mut);
    push(que, 1);
    push(que, 2);
    push(que, 3);
    push(que, 4);
    push(que, 5);
    printf("push\n");
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mut);
    return NULL;
}

void *thread_pop() { 
    pthread_mutex_lock(&mut);

    if (isEmpty(que)) {
        pthread_mutex_unlock(&mut); // lockをかける理由としてifまでの間にメソッドが入らないようにするため
        pthread_cond_wait(&cond, &mut); // 解放した後はまたロック
    }

    pop(que);
    pthread_mutex_unlock(&mut); // unlock 
    return NULL;
}

int main() {

    pthread_t th1, th2, th3;

    que = newQueue();


    pthread_create(&th1, NULL, thread_push, NULL);
    pthread_create(&th2, NULL, thread_pop, NULL);
    pthread_create(&th3, NULL, thread_pop, NULL);

    pthread_join(th1, NULL); 
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);

    pthread_mutex_destroy(&mut);

    if (pthread_cond_destroy(&cond) != 0) {
        perror("pthread_cond_destroy"); return -1;
    }

    print_node(que->head);
    deleteQueue(que);

    return 0;

}