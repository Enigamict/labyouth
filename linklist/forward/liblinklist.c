#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

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

link_node *add_node(link_node *n, int data) {

    link_node *addnode;


    addnode = new_node(NULL, data);

    if (addnode == NULL) {
        return NULL;
    }

    while (n != NULL) {
        n = n->next;
    } 
    n = addnode;

    return n;
}


void print_node(link_node *n) {

    if (n == NULL) {
        printf("NULL\n");
    }

    while (n != NULL) {
        printf("%3d", n->data);
        n = n->next;
    }
}