#include <stdio.h> 
#include <stdbool.h>

#include "liblinklist.h"

int main() {
    link_node *n = NULL;
    int data;

    n = new_node(n, 1); 

    if (n == NULL) {
        printf("init error"); 
        return false;
    }


    if (add_node(n, 2, 0)) {
        print_node(n);
    }else{
        printf("add error"); 
        return false;
    }

    n = top_add_node(n, 3);

    if (n == NULL) {
        printf("add error"); 
        return false;
    }else{
        print_node(n);
    }

    if (retrieve_data_node(n, &data, 1)) {
        printf("out data:%d\n", data);
    }else{
        printf("out error"); 
        return false;
    }

    if (delete_node(n, 3)) {
        print_node(n);
    }else{
        printf("delete error"); 
        return false;
    }

    if (add_node(n, 4, 0)) {
        print_node(n);
    }else{
        printf("add error"); 
        return false;
    }
}