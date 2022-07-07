#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "liblinklist.h"


link_node *new_node(link_node *prev, link_node *next, int data) {

    link_node *newnode;

    newnode = malloc(sizeof(link_node));

    if (newnode == NULL) {
        return NULL;
    }

    newnode->data = data;
    newnode->prev = prev;
    newnode->next = next;
    return newnode;
}

void destroy_node(link_node *n) {

    free(n);
}

int retrieve_data_node(link_node *n, int *data, const size_t index) {

    link_node *popnode;
    popnode = seek_node(n, index);
    if (popnode == NULL) {
        return false;
    }

    *data = popnode->data;

    return true;
}

link_node *delete_node(link_node *root, int index) {


    if (index == 0) {
        link_node *newroot = root->next;
        destroy_node(root);
        newroot->prev = NULL;
        return newroot;
    }

    link_node *cpnode = seek_node(root, index - 1);

    link_node *del_node = cpnode->next;
    cpnode->next = cpnode->next->next;
    cpnode->next->prev = cpnode;
    destroy_node(del_node);

    return root;
}

link_node *seek_node(link_node *root, size_t n) {

    for (size_t i = 0; i < n; i++) {
        root = root->next;
    }

    return root;

}

link_node *seek_tail(link_node *root) {

    while (root->next != NULL) {
        root = root->next;
    }

    return root;
}

link_node *add_node(link_node *root, int data) {

    link_node *prev;

    prev = seek_tail(root);

    if (prev == NULL) {
        return NULL;
    }

    link_node *addnode;

    addnode = new_node(prev, NULL, data);

    if (addnode == NULL) {
        return NULL;
    }

    prev->next = addnode;
    return root;
}

void print_node(link_node *n) {

    printf("list [");
    for (int i = 1; n != NULL; i++, n = n->next){
        printf("%3d", n->data);
    }
    printf("]\n");
}
