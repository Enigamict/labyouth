#pragma once

#include "../doubly/liblinklist.h"

#include <stdbool.h>

typedef struct queue {
    struct link_node *head; 
    struct link_node *tail; 
}queue;

queue *newQueue();
void deleteQueue(queue *stack);