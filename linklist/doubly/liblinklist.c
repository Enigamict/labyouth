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

    link_node *popNode;
    popNode = seek_node(n, index);
    if (popnode == NULL) {
        return false;
    }

    *data = popNode->data;

    return true;
}

link_node *delete_node(link_node *root, int index) {


    if (index == 0) {
        link_node *newRoot = root->next;
        destroy_node(root);
        newroot->prev = NULL;
        return newRoot;
    }

    link_node *cpNode = seek_node(root, index - 1);

    link_node *delNode = cpNode->next;
    cpNode->next = cpNode->next->next;
    cpNode->next->prev = cpNode;
    destroy_node(delNode);

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

    link_node *searchNode;

    searchNode = seek_tail(root);

    if (prev == NULL) {
        return NULL;
    }

    link_node *addNode;

    addNode = new_node(searchNode, NULL, data);

    if (addNode == NULL) {
        return NULL;
    }

    searchNode->next = addNode;

    return root;
}

void print_node(link_node *n) {

    printf("list [");
    for (int i = 1; n != NULL; i++, n = n->next){
        printf("%3d", n->data);
    }
    printf("]\n");
}
