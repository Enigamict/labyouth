#include <stdio.h>
#include <stdbool.h>

#include "libqueue.h"

int main() {
    stream_queue *q;
    int data;

    q = queue_init(5);
    
    if (q == NULL) { 
        printf("init error"); 
        return false;
    }

    if (queue_enqueue(q, 1)) {
        queue_print(q);
    }else{
        printf("enqueue error");
        return false;
    }

    if (queue_dequeue(q, &data)) {
        queue_print(q);
    }else{
        printf("dequeue error\n");
        return false;
    }

    queue_destroy(q);
}
