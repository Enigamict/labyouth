#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "libstack.h"

stream_stack *stack_init(int size) {

    stream_stack *s;
    s = malloc(sizeof(stream_stack));
    if (s == NULL) {
        return NULL;
    }
    s->bytedata = NULL;
    s->size = size;
    return s;
}

void stack_destroy(stream_stack *p) {

    if (!p)
        return;
    free(p);
}

int stack_push(int data, stream_stack *s) {
    if (s->num < s->size) {
        s->bytedata[s->num] = data;
        s->num ++;
        return 1;
    } else {
        return 0;
    }
}

int stack_pop(int *pop_data, stream_stack *s) { 
    if (s->num > 0) {
        s->num --;
        *pop_data = s->bytedata[s->num];
        return 1;
    } else {
        return 0;
    }
}

void stack_print(const stream_stack *s)
{
    int i;
    printf("stack [");
    for (i = 0; i < s->num; i++) {
        printf("%2d", s->bytedata[i]);
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