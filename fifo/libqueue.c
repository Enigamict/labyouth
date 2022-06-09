#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "libqueue.h"


stream_queue *queue_init(size_t size) {

    assert(size > 0);

    stream_queue *q;
    q = (stream_queue *)malloc(sizeof(stream_queue) + sizeof(int) * size);
    if (q == NULL) {
        return NULL;
    }

    q->size = size;
    q->head = 0;
    q->tail = 0;
    return q;
}

void queue_destroy(stream_queue *q) {

    free(q);
}

int queue_enqueue(stream_queue *q, int data) {

    if (q->tail == q->size) { // 現在追加出来る最後尾の値とqueueのサイズを比べてtailが超えているとpush出来ない
        return false;
    }

    q->data[(q->tail + q->head) % q->size] = data; // 最後尾の値と先頭の値を足して余りを出すことによって次の最後尾に追加するべきの添字が分かる
    q->tail++;
    return true;
}

int queue_dequeue(stream_queue *q, int *data) {

    if (q->tail == 0) {
        return false;
    }

    *data = q->data[q->head];
    q->head = (q->head + 1) % q->size; // 先頭の管理はpopした時に行う、リングバッファのため先頭の値も余りを使用しながら増やしていく
    q->tail--;
    return true;
}

void queue_print(const stream_queue *q) {

    printf("queue [");
    for(size_t i = 0; i < q->size; i++){
        printf("%3d", q->data[i]);
    }
    printf("]\n");
}