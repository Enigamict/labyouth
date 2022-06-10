#include <stdio.h> 
#include "liblinklist.h"

int main() {
    link_node *n = NULL;

    n = add_node(n, 2); 
    n = add_node(n, 3); 
    print_node(n);
    destroy_node(n); 
}