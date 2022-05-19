#include <stdio.h>
#include <string.h>

#define STACK_SIZE  100   

struct stack {
    int num;
    int data[100];
};

int push(int data, struct stack *s) {
    if (s->num < STACK_SIZE) {
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
        s->data[s->num];
        return 0;
    } else {
        return 1;
    }
}

void stackprint(struct stack *s)
{
    int i;
    printf("stack [");
    for (i = 0; i < s->num; i++) {
        printf("%d", s->data[i]);
    }
    printf("]\n");
}

int main() {
    int i, p, num;
    struct stack s;
    memset(&s, 0, sizeof(s));
    
    for (i = 1; i<=5 ; i++) {     
        push(i, &s);                  
        stackprint(&s);
    } 
    for (i = 1; i <= 3; i++) {
        pop(&s);
        stackprint(&s);
    }
}

