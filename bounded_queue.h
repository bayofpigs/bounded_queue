/********************************************************************
 * Filename: bounded_queue.h
 * Author: Mike Zhang
 ********************************************************************/

#ifndef BOUNDED_QUEUE_H
#define BOUNDED_QUEUE_H

/*******************************************************************
 * In the general case, a bounded queue is a FIFO data structure
 * for storing integers. It supports to operations, enqueue and
 * dequeue and has a limited size defined in n.
 *******************************************************************/
typedef struct BoundedQueue* BoundedQueue_T;

/*************  Bounded Queue Method Declarations *****************/
/***********************************************************
 * Returns a new Bounded Queue object of size iSize or NULL
 * if there is insufficient memory on the heap
 ***********************************************************/
BoundedQueue_T BoundedQueue_new(int iSize);

/********************************************************
 * Frees the bounded queue oBoundedQueue from memory
 ********************************************************/
void BoundedQueue_free(BoundedQueue_T oBoundedQueue);

/********************************************************
 * Obtain the number of integers in the bounded queue
 * oBoundedQueue
 ********************************************************/
int BoundedQueue_getLength(BoundedQueue_T oBoundedQueue);

/********************************************************
 * Obtain the max size of the bounded queue
 * oBoundedQueue
 ********************************************************/
int BoundedQueue_getCapacity(BoundedQueue_T oBoundedQueue);

/********************************************************
 * Enqueue a new integer, iNewInt into bounded queue, 
 * oBoundedQueue if oBoundedQueue is not full.
 * Return 1 on success, 0 on failure
 ********************************************************/
int BoundedQueue_enqueue(BoundedQueue_T oBoundedQueue,
                            int iNewInt);

/********************************************************
 * Dequeue  an integer from the bounded 
 * queue oBoundedQueue if the queue is nonempty. Inserts
 * the dequeued integer into the location of result.
 * Returns 1 on success, 0 on failure.
 ********************************************************/
int BoundedQueue_dequeue(BoundedQueue_T oBoundedQueue,
                          int* result);

#endif
