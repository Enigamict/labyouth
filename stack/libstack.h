#pragma once

struct stack {
    int size;
    int num;
    int *data;
};

int *stack_init(struct stack *s, int size);
void *stack_destroy(int *p);
int push(int data, struct stack *s);
int pop(struct stack *s);