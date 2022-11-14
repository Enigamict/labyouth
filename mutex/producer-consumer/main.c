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

    printf("que push = %p\n", que);
    push(que, 1);
    printf("push\n");
    pthread_mutex_unlock(&mut);
    pthread_cond_broadcast(&cond);
    return NULL;
}

void *thread_pop() { 
    pthread_mutex_lock(&mut);

    printf("que pop = %p\n", que);
    if (isEmpty(que)) {
        //pthread_mutex_unlock(&mut); // lockをかける理由としてifまでの間にメソッドが入らないようにするため
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
    pop(que);

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