#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <libqueue.h>

#define MAX_NUM 100

void initqueue(stream_que *queue){
    queue->head = 0;
    queue->tail = -1;
}

int enqueue(stream_que *queue, int data){

    if((queue->tail + 2) % MAX_NUM == queue->head){
        return 1;
    }else{
    queue->bytedata[(queue->tail + 1) % MAX_NUM] = data;
    queue->tail = (queue->tail + 1) % MAX_NUM;
    }
    return 0;
}

int dequeue(stream_que *queue){

    if((queue->tail + 1) % MAX_NUM == queue->head){
        return 1;
    }else{
        queue->head = (queue->head + 1) % MAX_NUM;
    }
    return 0;
}

void printQueue(stream_que *queue){
    int i = 0;
    int num;

    if (queue->tail < queue->head) {
        num = queue->tail + MAX_NUM - queue->head + 1;
    } else {
        num = queue->tail - queue->head + 1;
    }

    printf("que [");
    for(i = 0; i < num; i++){
        printf("%d", queue->bytedata[(queue->head + i) % MAX_NUM]);
    }
    printf("]\n");
}