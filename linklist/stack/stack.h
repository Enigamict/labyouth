#pragma once

#include "../doubly/liblinklist.h"

#include <stdbool.h>
#include <stddef.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct stack {
    struct link_node *head; 
    struct link_node *tail;

    size_t len;
}stack;

typedef struct stack_addr {
    struct in_addr addr;
}stack_addr;

stack *newStack();
void deleteStack(stack *stack);
stack *push_back(stack *stack, int data, const char *addr);
void pop_back(stack *stack);
int peek(stack *stack);
bool isEmpty(stack *stack);
size_t get_size(const stack *stack);