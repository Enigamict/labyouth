#pragma once


typedef struct link_node {
    struct link_node *next; 
    int data;
}link_node;

link_node *new_node(link_node *n, int data);
void destroy_node(link_node *n);
link_node *top_add_node(link_node *n, int data);
link_node *add_node(link_node *n, int data);
void print_node(link_node *n);