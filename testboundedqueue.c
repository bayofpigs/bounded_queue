/********************************************************************
 * Filename: testboundedqueue.c
 * Author: Mike Zhang
 * Some testing code (esp. Assure macro) inspired by
 * Robert Dondero's Princeton COS 217 teaching material                 
 ********************************************************************/
#include "bounded_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*--------------------------------------------------------------------*/
#define ASSURE(i) assure(i, __LINE__)

/*--------------------------------------------------------------------*/

/* If !iSuccessful, print a message to stdout indicating that the
   test at line iLineNum failed. */

static void assure(int iSuccessful, int iLineNum)
{
   if (! iSuccessful)
   {
      printf("Test at line %d failed.\n", iLineNum);
      fflush(stdout);
   }
}

/*--------------------------------------------------------------------*/

/* Basic Bounded Queue functionality */
static void testBasics(void) {
  BoundedQueue_T oBoundedQueue;
  int iSuccessful; 
  int value;
  int i;
  int counter;
  int TEST_SIZE = 100;

  printf("----------------------------------------------------------\n");
  printf("Testing basic bounding queue methods.\n");
  printf("No output should appear here.\n");
  fflush(stdout);

  /* Create a new bounded queue with size TEST_SIZE */
  oBoundedQueue = BoundedQueue_new(TEST_SIZE); 
  ASSURE(oBoundedQueue != NULL);
  ASSURE(BoundedQueue_getCapacity(oBoundedQueue) == TEST_SIZE);

  /* Test enqueue and size */
  for (i = 0; i < TEST_SIZE; i++) {
    iSuccessful = BoundedQueue_enqueue(oBoundedQueue, i);
    ASSURE(iSuccessful);
    ASSURE(BoundedQueue_getLength(oBoundedQueue) == (i + 1));
  }

  iSuccessful = BoundedQueue_enqueue(oBoundedQueue, 0);
  ASSURE(!iSuccessful);

  /* Test dequeue */
  /* Should dequeue numbers from 1...(TEST_SIZE - 1) inclusive */
  counter = 0;
  while (BoundedQueue_getLength(oBoundedQueue) > 0) {
    iSuccessful = BoundedQueue_dequeue(oBoundedQueue, &value);
    ASSURE(iSuccessful);
    ASSURE(value == counter);

    ASSURE(BoundedQueue_getLength(oBoundedQueue) == 
        (TEST_SIZE - counter - 1));
    counter++;
  }

  iSuccessful = BoundedQueue_dequeue(oBoundedQueue, &value);
  ASSURE(!iSuccessful);

  /* Test free: run with valgrind to check for memory errors */
  BoundedQueue_free(oBoundedQueue);
}

/*--------------------------------------------------------------------*/
static void testSingleInsertSingleRemove(void) {
  BoundedQueue_T oBoundedQueue;
  int iSuccessful;
  int i;
  int value;
  int TEST_SIZE = 100;

  printf("----------------------------------------------------------\n");
  printf("Testing single insertion single removal.\n");
  printf("No output should appear here.\n");
  fflush(stdout);

  oBoundedQueue = BoundedQueue_new(TEST_SIZE);
  ASSURE(oBoundedQueue != NULL);  

  for (i = 0; i < TEST_SIZE; i++) {
    iSuccessful = BoundedQueue_enqueue(oBoundedQueue, i);
    ASSURE(iSuccessful); 
    ASSURE(BoundedQueue_getLength(oBoundedQueue) == 1);
    
    iSuccessful = BoundedQueue_dequeue(oBoundedQueue, &value);
    ASSURE(iSuccessful);
    ASSURE(value == i);
    ASSURE(BoundedQueue_getLength(oBoundedQueue) == 0);
  }

  /* Free: run with valgrind to check for memory errors */
  BoundedQueue_free(oBoundedQueue);
}

/*--------------------------------------------------------------------*/
static void testBoundary(void) {
  BoundedQueue_T oBoundedQueue;  
  int iSuccessful;
  int i, j;
  int TEST_SIZES[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000};
  int NUM_SIZES = sizeof(TEST_SIZES) / sizeof(int);

  printf("----------------------------------------------------------\n");
  printf("Testing single insertion up to boundary.\n");
  printf("No output should appear here.\n");
  fflush(stdout);
  
  for (i = 0; i < NUM_SIZES; i++) {
    oBoundedQueue = BoundedQueue_new(TEST_SIZES[i]);
    ASSURE(oBoundedQueue != NULL);

    for (j = 0; j < TEST_SIZES[i]; j++) {
      iSuccessful = BoundedQueue_enqueue(oBoundedQueue, i);
      ASSURE(iSuccessful); 
    }

    iSuccessful = BoundedQueue_enqueue(oBoundedQueue, 0);
    ASSURE(!iSuccessful);

    BoundedQueue_free(oBoundedQueue);
  }
}

/*--------------------------------------------------------------------*/
static void stressTest(int iInsertions) {
  BoundedQueue_T oBoundedQueue;
  int i;
  int iSuccessful;
  int value;

  printf("----------------------------------------------------------\n");
  printf("Stress Testing.\n");
  printf("No output should appear here.\n");
  fflush(stdout);

  oBoundedQueue = BoundedQueue_new(iInsertions);
  ASSURE(oBoundedQueue != NULL); 

  for (i = 0; i < iInsertions; i++) {
    iSuccessful = BoundedQueue_enqueue(oBoundedQueue, i);
    ASSURE(iSuccessful);
  }

  iSuccessful = BoundedQueue_enqueue(oBoundedQueue, i);
  ASSURE(!iSuccessful); 

  for (i = 0; i < iInsertions; i++) {
    iSuccessful = BoundedQueue_dequeue(oBoundedQueue, &value);
    ASSURE(iSuccessful);
    ASSURE(value == i);
  }

  BoundedQueue_free(oBoundedQueue);
}

/*--------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
  int iInsertions;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s insertions\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (sscanf(argv[1], "%d", &iInsertions) != 1) {
    fprintf(stderr, "insertions must be numeric\n");
  }

  testBasics();
  testSingleInsertSingleRemove();
  testBoundary();
  stressTest(iInsertions);

  printf("----------------------------------------------------------\n");
  printf("End of test file\n");
  return 0;
}
