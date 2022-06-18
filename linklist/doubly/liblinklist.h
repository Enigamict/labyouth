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
int retrieve_data_node(link_node *n, int *data, int point);

/**
 * Delete the Linkedlist node
 *
 * @param n Take node arguments
 * @param point node to point
 * @return if the point is less than false
 *         
 */
int delete_node(link_node *n, int point);

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
int add_node(link_node *n, int data);

/**
 * Print the Linkedlist node
 *
 * @param n Take node arguments
 *         
 */
void print_node(link_node *n);