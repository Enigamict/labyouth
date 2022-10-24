#pragma once

#include "../doubly/liblinklist.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct queue {
    struct link_node *head; 
    struct link_node *tail;
    size_t len; 

}queue;

queue *newQueue();
void deleteQueue(queue *queue);
queue *push(queue *queue, int data);
void pop(queue *queue);
int top(queue *queue);
bool isEmpty(queue *queue);