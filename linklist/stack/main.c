#include <stdio.h> 
#include <stdbool.h>

#include <stack.h>

int main() {
    stack *n = NULL;

    n = newStack();

    push_back(n, 1);
    print_node(n->head);
    printf("%ld\n", get_size(n)); 
    pop_back(n);

    print_node(n->head);
    deleteStack(n);
}