#include <stdio.h> 
#include <stdbool.h>

#include "liblinklist.h"

int main() {
    link_node *n = NULL;

    n = new_node(NULL, NULL, 1);
    n = add_node(n, 2);
    n = add_node(n, 3);
    n = add_node(n, 4);
    n = add_node(n, 5);
    print_node(n);
}