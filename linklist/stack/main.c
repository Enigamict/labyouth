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
    print_node(n->head);
    printf("%ld\n", get_size(n)); 

    print_node(n->head);
    deleteStack(n);
}