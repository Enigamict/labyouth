#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define STACK_MAX_DEFAULT_SIZE 100
#define TRUE 1
#define FALSE 0

typedef struct stream_stack {
    size_t maxSize;
    size_t stackIndex;

    int data[];
}stream_stack;

stream_stack *stack_init(size_t size);
void stack_destroy(stream_stack *p);

int stack_push(int data, stream_stack *s);
int stack_pop(int *pop_data , stream_stack *s);
void stack_print(const stream_stack *s);