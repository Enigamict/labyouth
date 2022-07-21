#include <stdio.h> 
#include <stdbool.h>

#include <liblinklist.h>

int main() {
    link_node *n = NULL;
    int data;

    n = new_node(NULL, NULL, 1);
    n = tail_add_node(n, 2);
    n = tail_add_node(n, 3);
    n = tail_add_node(n, 4);
    n = head_get_data(n, &data);
    printf("%d", data);
    print_node(n);
}