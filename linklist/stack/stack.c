#include <stack.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

stack *newStack() {

    stack *node = malloc(sizeof(stack));

    if (!node)
        return NULL;
    return node;
}

void deleteStack(stack *stack) {

    free(stack);
}

stack *push_back(stack *stack, int data) {

    link_node *node;

    if (!stack->head) {
        node = new_node(data);

        stack->head = node;
        stack->tail = node;
        stack->tail->prev = NULL;
        return stack;
    }

    node = new_node(data);
    node->prev = stack->tail;

    stack->tail->next = node;
    stack->tail = node;
    return stack;
}

stack *pop_back(stack *stack) {

    link_node* tail = stack->tail;
    stack->tail = stack->tail->prev;
    destroy_node(tail);
    return stack;
}


int peek(stack *stack) {

    int data;
    data = stack->tail->data;
    return data;
}

bool isEmpty(stack *stack) {

    if (!stack->head && !stack->tail) return true;

    return false;
}