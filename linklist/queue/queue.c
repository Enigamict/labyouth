#include <queue.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

queue *newQueue() {

    queue *node = malloc(sizeof(queue));

    if (!node)
        return NULL;
    return node;
}

void deleteQueue(queue *stack) {

    free(stack);
}
