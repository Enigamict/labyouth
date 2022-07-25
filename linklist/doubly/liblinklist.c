#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "liblinklist.h"


link_node *new_node(int data) {

    link_node *newnode;

    newnode = malloc(sizeof(link_node));

    if (newnode == NULL) {
        return NULL;
    }

    newnode->data = data;

    return newnode;
}

void destroy_node(link_node *n) {

    free(n);
}

link_node *delete_node(link_node *root, link_node *node) {

    if (root == node) {
        link_node *newRoot = root->next;
        destroy_node(node);
        newRoot->prev = NULL;
        return newRoot;
    }

    link_node *next = node->next;
    link_node *prev = node->prev;

    prev->next = next;

    if (next) 
        next->prev = prev;
    
    destroy_node(node);
    return root;
}

link_node *seek_node(link_node *root, int data) {
 
    while (root) {
        if (data == root->data) return root;
        root = root->next;
    }

    return NULL;
}


link_node *seek_tail(link_node *root) {

    while (root->next != NULL) {
        root = root->next;
    }

    return root;
}


link_node *add_next_node(link_node *root, int data) {

    link_node *addNode;

    addNode = new_node(data);

    if (!addNode)
        return NULL;

    addNode->prev = root;

    link_node *prev = addNode->prev;
    link_node *next = root->next;

    prev->next = addNode;

    addNode->next = next;
    return root;
}

link_node *pop_node(link_node *root) {

    destroy_node(root);
    return root;
}

link_node *pop_front(link_node *root) {

    link_node* next = root->next;

    next->prev = NULL;

    destroy_node(root);
    return next;
}

void print_node(link_node *n) {

    printf("list [");
    for (int i = 1; n != NULL; i++, n = n->next){
        printf("%3d", n->data);
    }
    printf("]\n");
}

void print_prev_node(link_node *n) {
 
    link_node *prev = seek_tail(n);

    printf("list [");
    for (int i = 1; prev != NULL; i++, prev = prev->prev){
        printf("%3d", prev->data);
    }
    printf("]\n");
}