Bounded Queue
=============
A bounded queue abstract data type implementation in c for
KPCB

Running Tests:
To run standard tests 
```
make test
```

To run memory tests (assumes valgrind is installed)
```
make test_mem
```

To build the test files without running them
```
make
```

Description:
------------
A bounded queue is a fixed-sized FIFO data structure that
supports 2 primary commands: enqueue and dequeue.

Summary of included files:
---------------------------
1. bounded_queue.h: A header file defining the api of the bounded queue
2. bounded_queue.c: A C-based implementation of the api
3. testboundedqueue.c: A bounded_queue test client
4. Makefile: a makefile for quick compilation

Abridged summary of API:
-------------------------
1. BoundedQueue_new(int iSize): Bounded queue abstract data type 
constructor. Returns a pointer to a new bounded queue data structure or
NULL on failure.
2. BoundedQueue_enqueue(BoundedQueue_T, int iNew): Enqueue an integer
iNew into the bounded queue BoundedQueue_T. Returns 0 on failure,
1 on success.
3. BoundedQueue_dequeue(BoundedQueue_T, int * value): Dequeues an 
integer from the bounded queue and inserts its value int value. Returns
0 on failure, 1 on success.
