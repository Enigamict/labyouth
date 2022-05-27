#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack/libstack.h"

int main() {
    stream_stack s;
    int *p;
    int pop_data;

    memset(&s, 0, sizeof(s));
    p = stack_init(&s, 25);

    stack_push(1, &s);
    stack_pop(&pop_data,&s);
    printf("%d", pop_data);
    stack_print(&s);
    stack_destroy(p);
}