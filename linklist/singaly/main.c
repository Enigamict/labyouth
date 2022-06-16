#include <stdio.h> 
#include "liblinklist.h"

int main() {
    link_node *n = NULL;
    int data;

    n = new_node(n, 1); 

    add_node(n, 2, 0); 
    add_node(n, 3, 0); 
    add_node(n, 4, 0); 
    delete_node(n, 2); 
    add_node(n, 5, 0); 
    add_node(n, 6, 0); 
    out_node(n, &data, 3);
    //printf("%d", data);
    print_node(n);
}