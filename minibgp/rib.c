#include "rib.h"

struct bgp_rib *bgpInitRib() {

    struct bgp_rib *node = malloc(sizeof(struct bgp_rib));

    if (!node) {
        return NULL;
    }

    node->head = NULL;
    node->tail = NULL;

    return node;
}

struct bgprib_link_node *new_node(uint32_t data) {

    struct bgprib_link_node *node;

    node = malloc(sizeof(struct bgprib_link_node));

    if (node == NULL) {
        return NULL;
    }

    node->prefix = data;
    node->origin = 0;
    node->as_path = 0;
    node->as_path_length = 0;
    node->next_hop = 0;
    node->med = 0;
    node->local_pref = 0;

    return node;
}

struct bgprib_link_node *add_next_node(struct bgprib_link_node *node, uint32_t data) {

    struct bgprib_link_node  *addNode;

    addNode = new_node(data);

    if (!addNode) {
        return NULL;
    }

    struct bgprib_link_node  *next = node->next;
//
    node->next = addNode;
    addNode->next = next;
    addNode->prev = node;
//
    if (next) {
        next->prev = addNode;
    }
//
    return addNode;
}

void ribPop(struct bgp_rib *r) {

    if (r->head == NULL) {
        printf("pop error\n");
        return;
    }

    struct bgprib_link_node *node = pop_node(r->head);
    r->head = node;
}

struct bgp_rib *ribPush(struct bgp_rib *r, uint32_t data) {

    struct bgprib_link_node *node;

    if (!r->head) {
        node = new_node(data);

        r->head = node;
        r->tail = node;
        return r;
    }

    r->tail = add_next_node(r->tail, data);
    return r;
}

void destroy_node(struct bgprib_link_node *n) {

    free(n);
}

struct bgprib_link_node *pop_node(struct bgprib_link_node *node) {
 
    return delete_node(node);
}

 struct bgprib_link_node *delete_node(struct bgprib_link_node  *node) {

    if (node->prev == NULL && node->next == NULL) {
        return NULL;
    }

    if (!node->prev) {
        struct bgprib_link_node  *newRoot = node->next;
        destroy_node(node);
        newRoot->prev = NULL;
        return newRoot;
    }

    struct bgprib_link_node  *next = node->next;
    struct bgprib_link_node  *prev = node->prev;

    prev->next = next;

    if (next) {
        next->prev = prev;
    }

    destroy_node(node);
    return prev;

}
void print_node(struct bgprib_link_node *n) {

    printf("list [");
    for (int i = 1; n != NULL; i++, n = n->next){
        printf("%3x", n->prefix);
    }
    printf("]\n");
}