#include <stdio.h> 
#include <stdbool.h>

#include "liblinklist.h"

int main() {
    link_node *n = NULL;

    n = new_node(n, NULL, 1);
    add_node(n,2);
    add_node(n,3);
    print_node(n);
    destroy_node(n); 
}