#pragma once


typedef struct link_node {
    struct link_node *next; 
    struct link_node *prev; 
    int data;
}link_node;

/**
 * Initialize the Linkedlist node
 *
 * @param n Take node arguments
 * @param data Node add data
 * @return If malloc fails NULL
 *         
 */
link_node *new_node(link_node *prev, link_node *next, int data);

/**
 * Destroy the Linkedlist node
 *
 * @param n Take node arguments
 *         
 */
void destroy_node(link_node *n);

/**
 * Retrieve node data the Linkedlist node
 *
 * @param n Take node arguments
 * @param data retrieve data
 * @param point node to point
 * @return point to retrieve data 
 *         
 */
int retrieve_data_node(link_node *n, int *data, size_t point);

/**
 * Delete the Linkedlist node
 *
 * @param n Take node arguments
 * @param point node to point
 * @return if the point is less than false
 *         
 */
link_node *delete_node(link_node *root, int index);

/**
 * Top add the Linkedlist node
 *
 * @param n Take node arguments
 * @param data add data
 * @return returns node, or NULL if malloc fails. 
 *         
 */
link_node *top_add_node(link_node *n, int data);

/**
 * Data add the Linkedlist node
 *
 * @param n Take node arguments
 * @param data node to point
 * @return if malloc fails or add fails. 
 *         
 */
link_node *add_node(link_node *n, int data);

/**
 * Print the Linkedlist node
 *
 * @param n Take node arguments
 *         
 */
void print_node(link_node *n);
link_node *seek_node(link_node *root, size_t n);
link_node *seek_tail(link_node *root);