#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct stack {
    int size;
    int num;
    int *data;
};

int *stack_init(struct stack *s, int size) {
    s->data = (int *)malloc(sizeof(int) * size);
    s->size = size;
    return s->data;
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

int main() {
    int i;
    int *p;
    struct stack s;
    memset(&s, 0, sizeof(s));
    p = stack_init(&s, 25);
    
    for (i = 1; i<=20; i++) {     
        push(i, &s);                  
        stackprint(&s);
    } 
    for (i = 1; i <= 3; i++) {
        pop(&s);
        stackprint(&s);
    }
    free(p);
}

