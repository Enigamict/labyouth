#pragma once

 #include <assert.h>

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
link_node *new_node(int data);

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
int retrieve_data_node(link_node *n, int *data);

/**
 * Delete the Linkedlist node
 *
 * @param n Take node arguments
 * @param point node to point
 * @return if the point is less than false
 *         
 */
link_node *delete_node(link_node *node);

/**
 * Top add the Linkedlist node
 *
 * @param n Take node arguments
 * @param data add data
 * @return returns node, or NULL if malloc fails. 
 *         
 */

/**
 * Data add the Linkedlist node
 *
 * @param n Take node arguments
 * @param data node to point
 * @return if malloc fails or add fails. 
 *         
 */
link_node *add_next_node(link_node *n, int data);

/**
 * Print the Linkedlist node
 *
 * @param n Take node arguments
 *         
 */
void print_node(link_node *n);
void print_prev_node(link_node *n);
link_node *seek_node(link_node *root, int data);
link_node *seek_tail(link_node *root);
link_node *tail_add_node(link_node *n, int data);
link_node *pop_node(link_node *root);
link_node *pop_front_node(link_node *root);
link_node *add_prev_node(link_node *n, int data);