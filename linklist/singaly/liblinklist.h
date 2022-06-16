#pragma once


typedef struct link_node {
    struct link_node *next; 
    int data;
}link_node;

link_node *new_node(link_node *n, int data);
void destroy_node(link_node *n);
int out_node(link_node *n, int *data, int point);
int delete_node(link_node *n, int data);
link_node *top_add_node(link_node *n, int data);
int add_node(link_node *n, int data,int point);
void print_node(link_node *n);