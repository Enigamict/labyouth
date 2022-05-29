#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "libstack.h"

int *stack_init(stream_stack *s, int size) {
    s->data = (int *)malloc(sizeof(int) * size);
    if (s->data == NULL) {
        printf("malloc fail");
    }
    s->size = size;
    s->bytedata[0] = 0x7e;
    return s->data;
}

void stack_destroy(int *p) {
    free(p);
}

int stack_push(int data, stream_stack *s) {
    if (s->num < s->size) {
        s->data[s->num] = data;
        s->num ++;
        return 0;
    } else {
        return 1;
    }
}

int stack_pop(int *pop_data, stream_stack *s) { 
    if (s->num > 0) {
        s->num --;
        *pop_data = s->data[s->num];
        return 0;
    } else {
        return 1;
    }
}

void stack_print(const stream_stack *s)
{
    int i;
    printf("stack [");
    for (i = 0; i < s->num; i++) {
        printf("%2d", s->data[i]);
    }
    printf("]\n");
}

void test_stack_print(const stream_stack *s)
{
    int i;
    printf("stack [");
    for (i = 0; i < 5; i++) {
        printf("%2x", s->bytedata[i]);

    }
    printf("]\n");
}