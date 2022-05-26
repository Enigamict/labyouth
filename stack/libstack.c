#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libstack.h"

int *stack_init(struct stack *s, int size) {
    int *check;

    check = s->data = (int *)malloc(sizeof(int) * size);
    if (check == NULL) {
        printf("malloc fail");
    }
    s->size = size;
    return check;
}

void *stack_destroy(int *p) {
    free(p);
}

int push(int data, struct stack *s) {
    if (s->num < s->size) {
        s->data[s->num] = data;
        s->num ++;
        return 0;
    } else {
        return 1;
    }
}

int pop(struct stack *s) {
    
    if (s->num > 0) {
        s->num --;
        s->data[s->num] = 0;
        return 0;
    } else {
        return 1;
    }
}

void stackprint(const struct stack *s)
{
    int i;
    printf("stack [");
    for (i = 0; i < s->num; i++) {
        printf("%2d", s->data[i]);
    }
    printf("]\n");
}