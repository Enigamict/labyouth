#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct stream_stack {
    int size;
    int num;

    unsigned char *bytedata;
}stream_stack;

stream_stack *stack_init(int size);
void stack_destroy(stream_stack *p);
int stack_push(int data, stream_stack *s);
int stack_pop(int *pop_data , stream_stack *s);
void stack_print(const stream_stack *s);