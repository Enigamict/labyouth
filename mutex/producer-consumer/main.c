#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "../../linklist/queue/queue.h"

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; 

pthread_cond_t cond;
queue *que;

void *thread_push() { //producer

    pthread_mutex_lock(&mut);
    printf("--------------push-------------------\n");
    printf("que push = %p\n", que);
    push(que, 1);
    printf("push\n");
    pthread_mutex_unlock(&mut);
    pthread_cond_signal(&cond);
    printf("--------------push end---------------\n");
    return NULL;
}

void *thread_pop() { //consumer 
    pthread_mutex_lock(&mut);

    printf("--------------pop--------------------\n");
    printf("que pop = %p\n", que);

    while(isEmpty(que)) {
        printf("wait\n");
        pthread_cond_wait(&cond, &mut); // 解放した後はまたロック
        printf("wait end\n");
    }

    printf("pop\n");
    printf("que pop2 = %p\n", que);
    pop(que);
    printf("que pop2 list\n");
    printf("--------------pop end-----------------\n");
    pthread_mutex_unlock(&mut); // unlock 
    return NULL;
}

int main() {
    pthread_t th[256];

    que = newQueue();

    pthread_create(&th[0], NULL, thread_push, NULL);
    pthread_create(&th[1], NULL, thread_push, NULL);
    pthread_create(&th[2], NULL, thread_push, NULL);
    pthread_create(&th[3], NULL, thread_push, NULL);
    pthread_create(&th[4], NULL, thread_push, NULL);

    pthread_create(&th[5], NULL, thread_pop, NULL);
    pthread_create(&th[6], NULL, thread_pop, NULL);
    pthread_create(&th[7], NULL, thread_pop, NULL);
    pthread_create(&th[8], NULL, thread_pop, NULL);
    pthread_create(&th[9], NULL, thread_pop, NULL);
    pthread_create(&th[10], NULL, thread_pop, NULL);
    

    pthread_join(th[0], NULL);
    pthread_join(th[1], NULL);
    pthread_join(th[2], NULL);
    pthread_join(th[3], NULL);
    pthread_join(th[4], NULL);
    pthread_join(th[5], NULL);
    pthread_join(th[6], NULL);
    pthread_join(th[7], NULL);
    pthread_join(th[8], NULL);
    pthread_join(th[9], NULL);
    pthread_join(th[10], NULL);

    pthread_mutex_destroy(&mut);

    pthread_cond_destroy(&cond);

    print_node(que->head);
    deleteQueue(que);

    return 0;

}