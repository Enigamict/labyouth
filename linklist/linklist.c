#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 struct linklist {
    int data;
    struct linklist *next;
};

typedef struct foo {
    int data;
}foo;

struct linklist *newnode(struct linklist *n, int data) {
    struct linklist *newnode;

    newnode = malloc(sizeof(struct linklist));
    if (newnode == NULL) {
        printf("error");
    }
    newnode->data = data;
    newnode->next = n;
    return newnode;
}

int addnode(struct linklist **n, int data) {
    struct linklist *head_newnode;

    head_newnode = newnode(*n, data);
    if (head_newnode == NULL) {
        return 1;
    }
    *n = head_newnode;
    return 0;
}

struct linklist *topaddnode(struct linklist *n, int data) {
    struct linklist *head_newnode;

    head_newnode = newnode(n, data);
    if (head_newnode == NULL) {
        return head_newnode;
    }
    return head_newnode;
}
int tailaddnode(struct linklist **n, int data) {
    struct linklist *tail_newnode;

    tail_newnode = newnode(NULL, data);
    if (tail_newnode == NULL) {
        return 1;
    }
    while (*n != NULL) {
        n = &((*n)->next);
    } 
    *n = tail_newnode;
    return 0;
}

int nodeprint(const struct linklist *n) {
    printf("[");
    for(;;){
        printf("%d ", n->data);
        n = n->next;
        if (n == NULL) {
            break;
        }
    }
    printf("]\n");
    return 0; 
}

int checknodeprint(struct linklist **n, int point) {
    int i;
    for (i = 0; i < point && *n != NULL; i++) {
        n = &((*n)->next);
    }
    printf("check:%d", (*n)->data);
    return 0;
}

int main() {
    struct linklist *p = NULL;
    struct linklist *p1 = NULL;
    foo *test = NULL;

//    addnode(&p, 10);
    p1 = topaddnode(p1, 10);
    p1 = topaddnode(p1, 11);
    p1 = topaddnode(p1, 11);
    //addnode(&p, 11);
    checknodeprint(&p1, 0);
    //tailaddnode(&p, 12);
    nodeprint(p1);
    free(p1); 
}