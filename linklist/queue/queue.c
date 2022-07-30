#include <queue.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

queue *newQueue() {

    queue *node = malloc(sizeof(queue));

    if (!node)
        return NULL;

    node->head = NULL;
    node->tail = NULL;
    node->tail = NULL;

    return node;
}

void deleteQueue(queue *queue) {

    free(queue);
}

queue *push(queue *queue, int data) {

    link_node *node;

    if (!queue->head) {
        node = new_node(data);

        queue->head = node;
        queue->tail = node;
        return queue;
    }


    queue->tail = add_next_node(queue->tail, data);
    queue->len++;
    return queue;
}

void pop(queue *queue) {

    link_node *node = pop_front_node(queue->head);
    queue->head = node;
}

int top(queue *queue) {

    return queue->head->data;
}

bool isEmpty(queue *queue) {

    if (!queue->head && !queue->tail) return true;

    return false;
}