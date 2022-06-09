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

    if (!n)
        return;

    free(n);
}

link_node *top_add_node(link_node *n, int data) {

    link_node *addnode;

    addnode = new_node(n, data);

    if (addnode == NULL) {
        return NULL;
    }

    return addnode;
}

link_node *tail_add_node(link_node *n, int data) {

    link_node *addnode;

    addnode = new_node(n, data);

    if (addnode == NULL) {
        return NULL;
    }

    while (n != NULL) {
        printf("next");
        n = n->next;
        n = addnode;
    }
    printf("next");

    return n;
}

void print_node(link_node *n) {

    printf("[");
    for(;;){
        printf("%d ", n->data);
        n = n->next;
        if (n == NULL) {
            break;
        }
    }
    printf("]\n");
}