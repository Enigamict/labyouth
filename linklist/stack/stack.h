#pragma once

#include "../doubly/liblinklist.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct stack {
    struct link_node *head; 
    struct link_node *tail;

    size_t len;
}stack;

stack *newStack();
stack *push_back(stack *stack, int data);
stack *pop_back(stack *stack);
int peek(stack *stack);
bool isEmpty(stack *stack);