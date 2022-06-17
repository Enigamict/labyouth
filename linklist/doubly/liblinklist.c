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

int retrieve_data_node(link_node *n, int *data, int point) {

    if (point < 1) {
        return false;
    }

    for (int i = 1; n != NULL; i++, n = n->next){
        if (i == point)
            break;
    }

    *data = n->data;

    return true;
}

int delete_node(link_node *n, int point) {

    link_node *nextnode = NULL;

    if (point <= 1) {
        return false;
    }

    for (int i = 1; n != NULL; i++, n = n->next){
        if (i == point - 1)
            break;
    }

    nextnode = n->next->next;
    destroy_node(n->next);
    n->next = nextnode;
    return true;
}

int add_node(link_node *n, int data) {

    link_node *addnode;

    addnode = new_node(n, NULL, data);

    if (addnode == NULL) {
        return false;
    }

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
    for (int i = 1; n != NULL; i++, n = n->next){
        printf("%3d", n->data);
    }
    printf("]\n");
}