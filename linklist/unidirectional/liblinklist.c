#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "liblinklist.h"


link_node *new_node(link_node *n, int data) {

    link_node *newnode;

    newnode = malloc(sizeof(link_node));

    if (newnode == NULL) {
        return NULL;
    }

    newnode->data = data;
    newnode->next = n;
    return newnode;
}

void destroy_node(link_node *n) {

    free(n);
}

int retrieve_data_node(link_node *n, int *data, int index) {

    if (index < 0) {
        return false;
    }

    for (int i = 0; i < index; i++){
        n = n->next;
    }

    *data = n->data;

    return true;
}


link_node *delete_node(link_node *root, int index) {

    link_node *cpnode = root;

    if (index == 0) {
        link_node *new_root = root->next;
        destroy_node(root);
        return new_root;
    }

    for (int i = 0; i < index - 1; i++){
        cpnode = cpnode->next;
    }

    link_node *del_node = cpnode->next;
    cpnode->next = cpnode->next->next;
    destroy_node(del_node);
    return root;
}

int add_node(link_node *n, int data) {
    link_node *addnode;


        addnode = new_node(NULL, data);

        while (n->next != NULL) {
            n = n->next;
        }
        n->next = addnode;
        return true;
    

}

void print_node(link_node *n) {

    if (n == NULL) {
        printf("Node NULL\n");
    }

    printf("list [");
    for (int i = 0; n != NULL; i++, n = n->next){
        printf("%3d", n->data);
    }
    printf("]\n");
}