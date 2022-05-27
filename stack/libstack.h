#pragma once

typedef struct stream_stack {
    int size;
    int num;
    int *data;
}stream_stack;

int *stack_init(stream_stack *s, int size);
void stack_destroy(int *p);
int stack_push(int data, stream_stack *s);
int stack_pop(int *pop_data , stream_stack *s);
void stack_print(const stream_stack *s);