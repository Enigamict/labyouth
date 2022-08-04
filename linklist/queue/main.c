#include <stdio.h> 
#include <stdbool.h>

#include <queue.h>

int main() {
    queue *q = NULL;

    q = newQueue();

    push(q, 1, "1.1.1.1");
    push(q, 2, "1.1.1.2");
    push(q, 3, "1.1.1.3");
    push(q, 4, "1.1.1.4");
    push(q, 5, "1.1.1.5");

    print_node(q->head);
    pop(q);
    print_node(q->head);
    deleteQueue(q);
}