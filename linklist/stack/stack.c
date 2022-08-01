#include <stack.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

stack *newStack() {

    stack *node = malloc(sizeof(stack));

    if (!node)
        return NULL;

    node->head = NULL;
    node->tail = NULL;
    node->len = 0;

    return node;
}

void deleteStack(stack *stack) {

    link_node *node = NULL;
    link_node *next = NULL;

    for (node = stack->head; node != NULL; node = next) {
        next = NODE_NEXT(node);
        destroy_node(node);
    }

    stack->head = NULL;
    stack->tail = NULL;
    stack->len = 0;
    free(stack);
}

stack *push_back(stack *stack, int data) {

    link_node *node;

    if (!stack->head) {
        node = new_node(data);

        stack->head = node;
        stack->tail = node;
        return stack;
    }


    stack->tail = add_next_node(stack->tail, data);
    stack->len++;
    return stack;
}

void pop_back(stack *stack) {

    link_node *node = pop_node(stack->tail);
    stack->tail = node;
}

size_t get_size(const stack *stack) {

    size_t size = 0;
    const link_node *node = stack->head;

    while (node) {
        node = node->next;
        size++;
    } 

    return size;
}


int peek(stack *stack) {

    return stack->tail->data;
}

bool isEmpty(stack *stack) {

    if (!stack->head && !stack->tail) return true;

    return false;
}