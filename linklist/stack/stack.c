#include <stdio.h> 
#include <stdbool.h>

#include <liblinklist.h>

int main() {
    link_node *n = NULL;
    link_node *test = NULL;
    int data;

    n = new_node(NULL, NULL, 1);
    n = tail_add_node(n, 2);
    n = tail_add_node(n, 3);
    n = tail_add_node(n, 4);
    test = seek_node(n,3);
    n = test_add_node(n, test, 5);

    print_node(n);
}