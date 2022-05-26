#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack/libstack.h"

int main() {
    int *p;
    struct stack s;

    memset(&s, 0, sizeof(s));
    p = stack_init(&s, 25);
    stack_destroy(p);
    printf("test11\n");
}