#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "libstack.h"

stream_stack *stack_init(size_t size) {
    
    // Do not use value less 0
    assert(size > 0);

    stream_stack *s;
    s = (stream_stack *)malloc(sizeof(stream_stack) + sizeof(int) * size);
    if (s == NULL) {
        return NULL;
    }
    s->stackIndex = 0;
    s->maxSize = size;
    return s;
}

void stack_destroy(stream_stack *s) {

    free(s);
}

int stack_push(int data, stream_stack *s) {

    if (s->stackIndex == s->maxSize) {
        return false;
    }

    s->data[s->stackIndex] = data;
    s->stackIndex++;
    return true;
}

int stack_pop(int *pop_data, stream_stack *s) { 

    if (s->stackIndex > 0) {
        s->stackIndex--;
        *pop_data = s->data[s->stackIndex];
        return true;
    }else{
        return false;
    }

}

void stack_print(const stream_stack *s) {

    printf("stack [");
    for (size_t i = 0; i < s->stackIndex; i++) {
        printf("%2d", s->data[i]);
    }
    printf("]\n");
}
