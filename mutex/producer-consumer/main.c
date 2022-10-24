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

void* producer() {

    pthread_mutex_lock(&mut);
    push(que, 1);
    push(que, 2);
    printf("push\n");
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mut);
    return NULL;
}

void* consumer() { 
    pthread_mutex_lock(&mut);

    if (isEmpty(que)) {
        pthread_mutex_unlock(&mut);
        pthread_cond_wait(&cond, &mut);
    }

    pop(que);
    return NULL;
}

int main() {

    pthread_t th1, th2;

    que = newQueue();

    pthread_create(&th2, NULL, consumer, NULL);

    sleep(5);
    pthread_create(&th1, NULL, producer, NULL);

    pthread_join(th1, NULL); 
    pthread_join(th2, NULL);

    pthread_mutex_destroy(&mut);

    if (pthread_cond_destroy(&cond) != 0) {
        perror("pthread_cond_destroy"); return -1;
    }

    print_node(que->head);
    deleteQueue(que);

    return 0;

}