#include <stdio.h>
#include "libqueue.h"

int main() {
    stream_queue *q;
    int data;

    q = queue_init(QUEUE_MAX_DEFAULT_SIZE);
    
    if (q == NULL) {
        printf("init error");
    }

    if (queue_enqueue(q, 1)) {
        queue_print(q);
    }else{
        printf("enqueue error");
    }

    if (queue_dequeue(q, &data)) {
        queue_print(q);
    }else{
        printf("dequeue error\n");
    }

    queue_destroy(q);
}
