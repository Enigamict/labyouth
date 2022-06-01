#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct tree {
    int nodenum;

    struct tree *left;
    struct tree *right;
    unsigned char data[];
}tree;

tree *new_tree(int nodenum, int bytedata);
void destroy_tree(tree *tree);
tree *serch_tree(tree *tree, int nodenum);
tree *add_tree(tree *node, int nodenum, int bytedata);