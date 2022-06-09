#pragma once

#include <stddef.h>

typedef struct stream_stack {
    size_t maxSize;
    size_t stackIndex;

    int data[];
}stream_stack;

/**
 * Initialize the stack
 *
 * @param size Specify stack size
 * @return If malloc fails NULL
 *         
 */
stream_stack *stack_init(size_t size);

/**
 * Destory to stack
 *
 * @param s Takes the used stack argument
 *         
 */
void stack_destroy(stream_stack *p);

/**
 * Add to stack
 *
 * @param data Data add to the stack
 * @param s Takes the used stack argument
 * @return TRUE on success FAIL on capacity of the STACK 
 *         
 */
int stack_push(int data, stream_stack *s);


/**
 * pop to stack
 *
 * @param data Take a pointer and pop in the data from the stack.
 * @param s Takes the used stack argument
 * @return TRUE on success FAIL on stack no longer exists 
 *         
 */
int stack_pop(int *pop_data , stream_stack *s);

/**
 * Print to stack
 *
 * @param s Takes the used stack argument
 *         
 */
void stack_print(const stream_stack *s);