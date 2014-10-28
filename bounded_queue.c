/********************************************************************
 * Filename: bounded_queue.c
 * Author: Mike Zhang
 ********************************************************************/
#include <stdlib.h>
#include <assert.h>
#include "bounded_queue.h"

/*********************  Struct Declarations **********************/
/* A node in the bounded queue linked list */
struct ListNode {
  /* Value stored in this ListNode */
  int iValue;

  /* Pointer to the next value in the ListNode */
  struct ListNode* plNextNode;
};

/*******************************************************************
 * A bounded queue is a FIFO data structure
 * for storing integers. It supports to operations, enqueue and
 * dequeue and has a limited size defined in n.
 *******************************************************************/
struct BoundedQueue {
  /* The first node of the list */
  struct ListNode* plFirstNode;

  /* The last node of the list */
  struct ListNode* plLastNode;

  /* The number of elements in the Bounded Queue */
  int iSize;

  /* The maximum number of elements in the Bounded Queue */
  int iMaxSize;
};

/*************  Bounded Queue Method Declarations *****************/
/***********************************************************
 * Returns a new Bounded Queue object of size iSize or NULL
 * if there is insufficient memory on the heap
 ***********************************************************/
BoundedQueue_T BoundedQueue_new(int iSize) {
  BoundedQueue_T oBoundedQueue;
  oBoundedQueue = 
    (struct BoundedQueue*) malloc(sizeof(struct BoundedQueue));  
  if (oBoundedQueue == NULL) {
    return NULL;
  }

  oBoundedQueue->iSize = 0;
  oBoundedQueue->iMaxSize = iSize;

  oBoundedQueue->plFirstNode = NULL;
  oBoundedQueue->plLastNode = NULL;

  return oBoundedQueue;
}

/********************************************************
 * Frees the bounded queue oBoundedQueue from memory
 ********************************************************/
void BoundedQueue_free(BoundedQueue_T oBoundedQueue) {
  struct ListNode* plCurrent;
  struct ListNode* plNext;

  assert(oBoundedQueue != NULL);

  for (plCurrent = oBoundedQueue->plFirstNode; plCurrent != NULL;
      plCurrent = plNext) {
    plNext = plCurrent->plNextNode;   
    free (plCurrent);
  }

  free (oBoundedQueue);
}

/********************************************************
 * Obtain the number of integers in the bounded queue
 * oBoundedQueue
 ********************************************************/
int BoundedQueue_getLength(BoundedQueue_T oBoundedQueue) {
  assert(oBoundedQueue != NULL);

  return oBoundedQueue->iSize;
}

/********************************************************
 * Obtain the max size of the bounded queue
 * oBoundedQueue
 ********************************************************/
int BoundedQueue_getCapacity(BoundedQueue_T oBoundedQueue) {
  assert(oBoundedQueue != NULL);

  return oBoundedQueue->iMaxSize;
}

/********************************************************
 * Enqueue a new integer, iNewInt, into bounded queue, 
 * oBoundedQueue if oBoundedQueue is not full.
 * Return 1 on success, 0 on failure
 ********************************************************/
int BoundedQueue_enqueue(BoundedQueue_T oBoundedQueue,
                            int iNewInt) {

  struct ListNode* plNewNode;

  assert(oBoundedQueue != NULL);

  if (oBoundedQueue->iSize >= oBoundedQueue->iMaxSize) {
    return 0;
  }

  plNewNode = (struct ListNode*) malloc(sizeof(struct ListNode));
  if (plNewNode == NULL) {
    return 0;
  }

  plNewNode->iValue = iNewInt;
  plNewNode->plNextNode = NULL; 
  
  /* 
   * Invariants: let front, end be the front and end of the
   * double ended linked list. The possible states of front end
   * are:
   * 1. NULL, NULL = Empty/Initial state of the linked list, 
   *                 nothing inserted
   * 2. A,    A    = Where A is a ListNode. This state can only
   *                 occur when A is the first listnode to be 
   *                 inserted
   * 3. A,    B    = Where A, B are ListNodes. This is the general
   *                 case where number of nodes > 1
   */

  /* State 1: NULL, NULL 
   * Create a new ListNode and set plFirstNode and plLastNode to 
   * point to the new ListNode. Transitions to state 2. */
  if (oBoundedQueue->plFirstNode == NULL) {
    oBoundedQueue->plFirstNode = plNewNode;
    oBoundedQueue->plLastNode = plNewNode;
  } 

  /* State 2: A, A; State 3: A, B
   * Create a new ListNode and set the node next to plLastNode to
   * equal the NewNode. Set plLastNode to equal to the new ListNode.
   * Transitions to state 3                                 */
  else {
    oBoundedQueue->plLastNode->plNextNode = plNewNode; 
    oBoundedQueue->plLastNode = plNewNode;
  }
  
  oBoundedQueue->iSize++;
  return 1;
}

/********************************************************
 * Dequeue an integer from the bounded 
 * queue oBoundedQueue if the queue is nonempty, storing
 * the result in result. Returns 0 on failure (empty
 * queue) and 1 on success.
 ********************************************************/
int BoundedQueue_dequeue(BoundedQueue_T oBoundedQueue, int* result) {
  struct ListNode* temp;

  assert(oBoundedQueue != NULL);
  assert(result != NULL);

  /* 
   * Invariants: let front, end be the front and end of the
   * double ended linked list. The possible states of front end
   * are:
   * 1. NULL, NULL = Empty/Initial state of the linked list, 
   *                 nothing inserted
   * 2. A,    A    = Where A is a ListNode. This state can only
   *                 occur when A is the first listnode to be 
   *                 inserted
   * 3. A,    B    = Where A, B are ListNodes. This is the general
   *                 case where number of nodes > 1
   */
  /* State 1: NULL, NULL. Returns error code 0 (empty queue) */
  if (oBoundedQueue->plFirstNode == NULL) {
    return 0;
  }

  /* State 2: A, A. Returns the value stored in A. Transitions
   * to state 1                                       */
  else if (oBoundedQueue->plFirstNode == oBoundedQueue->plLastNode) {
    *result = oBoundedQueue->plFirstNode->iValue; 
    free(oBoundedQueue->plFirstNode);
    oBoundedQueue->plFirstNode = NULL;
    oBoundedQueue->plLastNode = NULL;
  }

  /* State 3: A, B. Returns the value stored in A. Transitions to
   * state 2 if there are only 2 elements in the list. Transitions
   * to state 3 otherwise                                   */
  else {
    *result = oBoundedQueue->plFirstNode->iValue;
    temp = oBoundedQueue->plFirstNode;  
    
    oBoundedQueue->plFirstNode = temp->plNextNode;
    free(temp);
  }
  
  oBoundedQueue->iSize--;
  return 1;
}
