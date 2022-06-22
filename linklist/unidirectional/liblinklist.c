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
    link_node *del_node = root;

    if (index == 0) {
        cpnode = root->next;
        destroy_node(root);
        return cpnode;
    }

    int i = 0;


    while(cpnode != NULL ) {
        if (i == index - 1) {
            del_node = cpnode->next;
            cpnode->next = cpnode->next->next;
            destroy_node(del_node);
            return root;
        }else{
            cpnode = cpnode->next;
            i++;
        }
    }
    return root;
}

int add_node(link_node *n, int data, int point) {
    link_node *addnode;

    addnode = new_node(NULL, data);

    if (addnode == NULL) {
        return false;
    }

    if (point != 0) {
        for (int i = 1; n != NULL; i++, n = n->next) {
            if (i == point)
                break;
        }
        addnode->next = n->next;
        n->next = addnode;
        return true;
    }else{
        while (n->next != NULL) {
            n = n->next;
        }
        n->next = addnode;
        return true;
    }

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