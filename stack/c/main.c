#include "libstack.h"

#include <stdio.h>
#include <stdbool.h>

int main() {

    stream_stack *s;
    int pop_data;
    int data = 1;

    s = stack_init(1);

    if (s == NULL) {
        printf("init error\n");
        return false;
    }

    if(stack_push(data, s)){
        stack_print(s);
    }else{
        printf("push error\n");
        return false;
    }

    if(stack_pop(&pop_data, s)) {
        printf("pop data:  %d\n", pop_data);
    }else{
        printf("pop error");
        return false;
    }

    stack_destroy(s);
}