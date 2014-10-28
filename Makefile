#----------------------------------------------------------------------
# Makefile
# Author: Mike Zhang 
# Note that valgrind related compilation targets require valgrind
# to be run
#----------------------------------------------------------------------

# Default
CC = gcc

# For valgrind
CCFLAGS = -g -O0

all: testboundedqueue testboundedqueue_valgrind

# valgrind object files
%_valgrind.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

# Default object files
%.o: %.c
	$(CC) $(CCFLAGS) -c $<

test: testboundedqueue
	./testboundedqueue 10000

test_mem: testboundedqueue_valgrind
	valgrind testboundedqueue 10000

testboundedqueue: bounded_queue.o testboundedqueue.o
	$(CC) bounded_queue.o testboundedqueue.o -o $@

testboundedqueue_valgrind: bounded_queue_valgrind.o \
  testboundedqueue_valgrind.o
	$(CC) $(CCFLAGS) bounded_queue_valgrind.o \
	  testboundedqueue_valgrind.o -o $@

clean:
	rm -f *.o

# Object dependencies
bounded_queue.o: bounded_queue.h
bounded_queue_valgrind.o: bounded_queue.h
testboundedqueue.o: bounded_queue.h
testboundedqueue_valgrind.o: bounded_queue.h
