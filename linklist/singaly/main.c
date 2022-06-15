#include <stdio.h> 
#include "liblinklist.h"

int main() {
    link_node *n = NULL;

    n = new_node(n, 10); 

    add_node(n, 2, 0); 
    add_node(n, 3, 0); 
    add_node(n, 4, 2); 
    delete_node(n, 2);
    print_node(n);
}