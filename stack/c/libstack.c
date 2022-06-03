#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "libstack.h"

/**
 * Initialize the stack
 *
 * @param size Specify stack size
 * @return If malloc fails NULL
 *         
 */
stream_stack *stack_init(size_t size) {
    
    // Do not use value less 0
    assert(size > 0);

    stream_stack *s;
    s = (stream_stack *)malloc(sizeof(stream_stack) + sizeof(int) * size);
    if (s == NULL) {
        return NULL;
    }
    s->maxSize = size;
    return s;
}

/**
 * Destory to stack
 *
 * @param s Takes the used stack argument
 * @return If malloc fails NULL
 *         
 */
void stack_destroy(stream_stack *s) {

    if (!s)
        return;
    free(s);
}

/**
 * Add to stack
 *
 * @param data Data add to the stack
 * @param s Takes the used stack argument
 * @return TRUE on success FAIL on capacity of the STACK 
 *         
 */
int stack_push(int data, stream_stack *s) {

    if (s->stackIndex < s->maxSize) {
        s->data[s->stackIndex] = data;
        s->stackIndex ++;
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * pop to stack
 *
 * @param data Take a pointer and pop in the data from the stack.
 * @param s Takes the used stack argument
 * @return TRUE on success FAIL on stack no longer exists 
 *         
 */
int stack_pop(int *pop_data, stream_stack *s) { 

    if (s->stackIndex > 0) {
        s->stackIndex --;
        *pop_data = s->data[s->stackIndex];
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * Print to stack
 *
 * @param s Takes the used stack argument
 *         
 */
void stack_print(const stream_stack *s) {

    if (!s)
        return;

    printf("stack [");
    for (size_t i = 0; i < s->stackIndex; i++) {
        printf("%2d", s->data[i]);
    }
    printf("]\n");
}
