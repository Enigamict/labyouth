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

int retrieve_data_node(link_node *n, int *data) {

    link_node *popNode;
    popNode = seek_next_tail(n);
    if (popNode == NULL) {
        return false;
    }

    *data = popNode->data;

    return true;
}

link_node *delete_node(link_node *root, link_node *node) {

    if (root == node) {
        link_node *newRoot = root->next;
        destroy_node(node);
        newRoot->prev = NULL;
        return newRoot;
    }

    if (node->next != NULL) {
        node->prev->next = node->next;
        node->prev->next->prev = node->prev;
        destroy_node(node);
        return root;
    }else{
        node->prev->next = NULL;
        destroy_node(node);
        return root;
    }

    return NULL;
}

link_node *seek_node(link_node *root, int data) {

    
    while (root->next != NULL) {
        if (data == root->data){
            return root;
        }
        root = root->next;
    }

    return NULL;

}


link_node *seek_next_tail(link_node *root) {

    while (root->next != NULL) {
        root = root->next;
    }

    return root;
}

link_node *seek_prev_tail(link_node *root) {

    while (root->next != NULL) {
        root = root->next;
    }

    return root;
}

link_node *add_node(link_node *root, int data) {

    link_node *searchNode;

    searchNode = seek_next_tail(root);

    if (searchNode == NULL) {
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

void print_prev_node(link_node *n) {
 
    link_node *prev = seek_next_tail(n);

    printf("list [");
    for (int i = 1; prev != NULL; i++, prev = prev->prev){
        printf("%3d", prev->data);
    }
    printf("]\n");
}