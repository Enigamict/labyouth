#pragma once


typedef struct link_node_uni {
    struct link_node *next; 
    int data;
}link_node_uni;

/**
 * Initialize the Linkedlist node
 *
 * @param n Take node arguments
 * @param data Node add data
 * @return If malloc fails NULL
 *         
 */
link_node *uni_new_node(link_node *n, int data);

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
 * @param index node to point
 * @return point to retrieve data 
 *         
 */
int retrieve_data_node(link_node *n, int *data, int index);

/**
 * Delete the Linkedlist node
 *
 * @param n Take node arguments
 * @param index node to point
 * @return If malloc fails NULL
 *         
 */
link_node *delete_node(link_node *root, int index);

/**
 * Queue type Data add the Linkedlist node
 *
 * @param n Take node arguments
 * @param data node to point
 * @return if malloc fails or add fails. 
 *         
 */
int add_node(link_node *n, int data);

/**
 * Print the Linkedlist node
 *
 * @param n Take node arguments
 *         
 */
void print_node(link_node *n);