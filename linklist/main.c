#include <stdio.h>

#include "liblinklist.h"

int main() {
    link_node *n = NULL;

    n = top_add_node(n, 11); 
    n = top_add_node(n, 12); 
    n = top_add_node(n, 13); 
    print_node(n);
}