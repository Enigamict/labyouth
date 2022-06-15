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

int top_out_node(link_node *n, int *data) {

    *data = n->data;

    return true;
}

link_node *top_add_node(link_node *n, int data) {

    link_node *addnode;

    addnode = new_node(n, data);

    if (addnode == NULL) {
        return NULL;
    }

    return addnode;
}

int delete_node(link_node *n, int data) {

    link_node *nextnode = NULL;

    for (int i = 1; n != NULL; i++, n = n->next){
        if (i == data)
            break;
    }

    nextnode = n->next;
    destroy_node(n);
    n->next = nextnode;
    return true;
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
        printf("a:%d", n->data);
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

    for (int i = 1; n != NULL; i++, n = n->next){
        printf("%3d", n->data);
    }
}