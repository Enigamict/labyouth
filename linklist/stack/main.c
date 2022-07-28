#include <stdio.h> 
#include <stdbool.h>

#include <stack.h>

int main() {
    stack *n = NULL;

    n = newStack();

    push_back(n, 1);
    push_back(n, 2);
    push_back(n, 3);
    push_back(n, 4);
    push_back(n, 5);
    print_node(n->tail);

    link_node *test = seek_node(n->tail, 2);
    add_next_node(test,6);
    print_node(n->tail);
    print_prev_node(n->tail);

}