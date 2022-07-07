#include <stdio.h> 
#include <stdbool.h>

#include "liblinklist.h"

int main() {
    link_node *n = NULL;

    n = new_node(NULL, NULL, 1);
    n = add_node(n, 2, 1);
    n = add_node(n, 3, 2);
    n = add_node(n, 4, 3);
    n = delete_node(n,1);
    printf("%d", n->next->next->prev->data);
    print_node(n);
}