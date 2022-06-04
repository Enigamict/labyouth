#include "libstack.h"

#include <stdio.h>

int main() {

    stream_stack *s;
    int pop_data;
    int data = 1;

    s = stack_init(STACK_MAX_DEFAULT_SIZE);

    if (s == NULL) {
        printf("init error\n");
        return FALSE;
    }

    if(stack_push(data, s)){
        stack_print(s);
    }else{
        printf("push error\n");
    }

    if(stack_pop(&pop_data, s)) {
        printf("pop data:  %d\n", pop_data);
    }else{
        printf("pop error");
    }

    stack_destroy(s);
}