#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct stream_stack {
    int size;
    int num;

    int *data;
    unsigned char bytedata[];
}stream_stack;

#define BYTE_DATA 256;

int *stack_init(stream_stack *s, int size);
void stack_destroy(int *p);
int stack_push(int data, stream_stack *s);
int stack_pop(int *pop_data , stream_stack *s);
void stack_print(const stream_stack *s);
void test_stack_print(const stream_stack *s);