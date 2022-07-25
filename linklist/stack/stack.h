#pragma once

#include "../doubly/liblinklist.h"

#include <stdbool.h>

typedef struct stack {
    struct link_node *head; 
    struct link_node *tail; 
}stack;

stack *newStack();
stack *push_back(stack *stack, int data);
stack *pop_back(stack *stack);
int peek(stack *stack);
bool isEmpty(stack *stack);