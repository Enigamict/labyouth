#include <stdio.h>

#define MAX_NUM 100

struct que {
    int tail;
    int head;
    int data[100];
};

void initqueue(struct que*queue){
    queue->head = 0;
    queue->tail = -1;
}

int enqueue(struct que *queue, int data){

    if((queue->tail + 2) % MAX_NUM == queue->head){
        return 1;
    }else{
    queue->data[(queue->tail + 1) % MAX_NUM] = data;
    queue->tail = (queue->tail + 1) % MAX_NUM;
    }
    return 0;
}

int dequeue(struct que *queue){

    if((queue->tail + 1) % MAX_NUM == queue->head){
        return 1;
    }else{
        queue->head = (queue->head + 1) % MAX_NUM;
    }
    return 0;
}

void printQueue(struct que *queue){
    int i = 0;
    int num;

    if (queue->tail < queue->head) {
        num = queue->tail + MAX_NUM - queue->head + 1;
    } else {
        num = queue->tail - queue->head + 1;
    }

    printf("que [");
    for(i = 0; i < num; i++){
        printf("%d", queue->data[(queue->head + i) % MAX_NUM]);
    }
    printf("]\n");
}

int main(){
    int i;
    struct que queue;

    initqueue(&queue);

    for (i = 1; i<=5 ; i++) {
        enqueue(&queue, i);
        printQueue(&queue);
    } 

    for (i = 1; i<=3; i++) {
        dequeue(&queue);
        printQueue(&queue);
    }

    return 0;
}