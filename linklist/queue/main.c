#include <stdio.h> 
#include <stdbool.h>

#include <queue.h>

int main() {
    queue *q = NULL;

    q = newQueue();

    push(q, 1);
    printf("adress :%x", q);
    push(q, 2);
    printf("adress :%x", q);

    print_node(q->head);
    pop(q);
    print_node(q->head);
    deleteQueue(q);
}