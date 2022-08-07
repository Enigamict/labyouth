#include <stdio.h> 
#include <stdbool.h>

#include "liblinklist.h"

int main() {
    link_node *n = NULL;

    n = new_node(1);
    add_next_node(n, 2);
    add_next_node(n, 3);
    add_next_node(n, 4);
    print_node(n);
}