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

void *thread_push() { //producer

    pthread_mutex_lock(&mut);

    printf("que push = %p\n", que);
    push(que, 1);
    printf("push\n");
    pthread_mutex_unlock(&mut);
    pthread_cond_broadcast(&cond);
    return NULL;
}

void *thread_pop() { //consumer 
    pthread_mutex_lock(&mut);

    printf("que pop = %p\n", que);
    if (isEmpty(que)) {
        printf("wait\n");
        pthread_cond_wait(&cond, &mut); // 解放した後はまたロック
        printf("wait end\n");
    }

    printf("pop\n");
    printf("que pop2 = %p\n", que);
    pop(que);
    pthread_mutex_unlock(&mut); // unlock 
    return NULL;
}
int main1() {
    que = newQueue();
    push(que, 1);
    pop(que);

    printf("%d", (isEmpty(que)));

    if (isEmpty(que))
    {
        push(que, 2);
    }

    print_node(que->head);

    return 1;
}

int main() {
    pthread_t th[256];

    que = newQueue();

    pthread_create(&th[0], NULL, thread_push, NULL);
    pthread_create(&th[1], NULL, thread_push, NULL);
    pthread_create(&th[2], NULL, thread_pop, NULL);
    pthread_create(&th[3], NULL, thread_pop, NULL);
//    for (int i = 0; i < 5; i++) {
//        pthread_create(&th[i], NULL, thread_push, NULL);
//    }
//
//    for (int i = 0; i < 5; i++) {
//        pthread_create(&th[i], NULL, thread_pop, NULL);
//    }

    pthread_join(th[0], NULL);
    pthread_join(th[1], NULL);
    pthread_join(th[2], NULL);
    pthread_join(th[3], NULL);

    pthread_mutex_destroy(&mut);

    if (pthread_cond_destroy(&cond) != 0) {
        perror("pthread_cond_destroy"); return -1;
    }

    print_node(que->head);
    deleteQueue(que);

    return 0;

}