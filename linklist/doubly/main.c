#include <stdio.h> 
#include <stdbool.h>

#include "liblinklist.h"

int main() {
    link_node *n = NULL;
    link_node *testnode = NULL;

    n = new_node(NULL, NULL, 1);
    n = add_node(n, 2);
    n = add_node(n, 10);
    n = add_node(n, 4);
    n = add_node(n, 6);
    print_node(n);

    testnode = seek_node(n,4);
    link_node *testtail = seek_next_tail(n);

    n = delete_node(n,testnode);

    print_node(n);
    print_prev_node(n);
}