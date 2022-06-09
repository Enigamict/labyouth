#pragma once

#include <stddef.h>

typedef struct stream_queue {
    size_t tail;
    size_t head;
    size_t size;
    
    int data[];
}stream_queue;

/**
 * Initialize the queue
 *
 * @param size Specify queue size
 * @return If malloc fails NULL
 *         
 */
stream_queue *queue_init(size_t size);


/**
 * Destroy the queue
 *
 * @param q Takes the used queue argument
 * @return If malloc fails NULL
 *         
 */
void queue_destroy(stream_queue *q);

/**
 * enqueue to queue
 * About the ring buffer
 * 1. When the ring buffer exceeds a certain size, it returns to the beginning and new data can be added from there.
 * 2. (q->tail + q->head) % (int)q->size .
 * 3. It will be possible to return to zero by taking out the remainder over the size.
 *
 * @param q Takes the used queue argument
 * @param size Specify queue size
 * @return TRUE on success FAIL on capacity of the QUEUE
 *         
 */
int queue_enqueue(stream_queue *q, int data);


/**
 * dequeue to queue
 * Like enqueue, it uses a ring buffer.
 *
 * @param q Takes the used queue argument
 * @param data Takes a pointer variable of type int
 * @return TRUE on success FAIL on capacity of the QUEUE
 *         
 */
int queue_dequeue(stream_queue *q, int *data);


/**
 * Print to queueue
 *
 * @param q Takes the used stack argument
 *         
 */
void queue_print(const stream_queue *q);