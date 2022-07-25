#include <stdio.h> 
#include <stdbool.h>

#include <liblinklist.h>

int main() {
    link_node *n = NULL;
    int data;

    n = new_node(1);
    tail_add_node(n, 2);
    tail_add_node(n, 3);
    tail_add_node(n, 4);
    print_node(n);
}