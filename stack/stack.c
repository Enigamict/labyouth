
#include <stdio.h>

#define STACK_SIZE  100   

struct stack {
    int num;
    int data[100];
};

int push(int data) {
    struct stack s;
    if (s.num < STACK_SIZE) {
        s.data[s.num] = data;
        s.num ++;
        return s.num;
    } else {
        return 1;
    }
}

int pop(int *data, int num) {
    struct stack s;
    if (num > 0) {
        num --;
        *data = s.data[num];
        return num;
    } else {
        return 1;
    }
}

void stackprint(int num)
{
    int i;
    struct stack s;
    printf("stack [");
    for (i = 0; i < num; i++) {
        printf("%d", s.data[i]);
    }
    printf("]\n");
}

int main() {
    int i, p, num;

    for (i = 1; i<=5 ; i++) {     
        num = push(i);                  
        stackprint(num);
    } 
    for (i = 1; i <= 3; i++) {
        num = pop(&p, num);
        stackprint(num);
    }
}

