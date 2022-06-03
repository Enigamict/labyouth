#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "libtree.h"

tree *new_tree(int nodenum, int bytedata) {

    tree *nodetree = (tree *)malloc(sizeof(tree));
    if (nodetree == NULL) {
        return NULL;
    }
    nodetree->nodenum = nodenum;
    nodetree->data[0] = bytedata;
    nodetree->left = NULL;
    nodetree->right = NULL;
    return nodetree;
}

void destroy_tree(tree *tree) {

    if (!tree)
        return;

    free(tree);
}

tree *serch_tree(tree *node, int nodenum) {

    tree *serch_node;
    serch_node = node;

    while (serch_node) {
        if (nodenum < serch_node->nodenum) {
            serch_node = node->left;
        }else if (nodenum > serch_node->nodenum) {
            serch_node = node->right;
        } else {
            return serch_node;
        }
    }

    return NULL; 
}

tree *add_tree(tree *node, int nodenum, int bytedata) {

    tree *addnode;

    if (node == NULL) {
        node = new_tree(nodenum, bytedata);
        if (node == NULL) {
            printf("error");
            return NULL;
        }
    }

    addnode = node;
    for(;;) {
        if (nodenum > addnode->nodenum) {
            if (addnode->right == NULL){
                node->right = new_tree(nodenum, bytedata);
                break;
            }
            // 右に移動
            addnode = addnode->right;
        }else if (nodenum < addnode->nodenum) {
            if (addnode->left == NULL){
                node->left = new_tree(nodenum, bytedata);
                break;
            }
            // 左に移動
            addnode = addnode->left; 
        }else{
            break;
        }
    }
    return node;
}