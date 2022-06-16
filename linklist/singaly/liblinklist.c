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

int out_node(link_node *n, int *data, int point) {

    for (int i = 1; n != NULL; i++, n = n->next){
        if (i == point)
            break;
    }

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

    if (data < 0){
        return false;
    }

    for (int i = 1; n != NULL; i++, n = n->next){
        if (i == data - 1)
            break;
    }

    printf("%d", n->next->data);
    nextnode = n->next->next;
    destroy_node(n->next);
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