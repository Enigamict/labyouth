#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree/libtree.h"

int main() {

    tree *node;

    node = NULL;

    node = add_tree(node,10, 0x00);
    node = add_tree(node,11, 0x07);
    node = add_tree(node,12, 0x09);
    node = add_tree(node,9, 0x07);
    node = add_tree(node,13, 0x09);
    node = add_tree(node,8, 0x09);
    node = serch_tree(node, 8);
    if (node == NULL) {
        printf("aa");
    }

    destroy_tree(node);
}