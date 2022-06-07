CC = gcc
MAIN = main.c 
LIBS = libqueue.c
CFLAGS = -Wall -Wextra -O2
DEBUGFLAGS = -Wall -Wextra -g

TESTINPATH = -I ./ -I ../lib/Unity/src -I ../lib/Unity/extras/fixture/src/ -I ../lib/Unity/extras/memory/src
UNITYPATH = ../lib/Unity/src/unity.c ../lib/Unity/extras/fixture/src/unity_fixture.c ../lib/Unity/extras/memory/src/unity_memory.c
TESTPATH = ../test/testcase/test_queue_init.c ../test/testcase/test_queue_enq.c ../test/testcase/test_queue_deq.c ../test/testrun/test_run.c ../test/testrun/all_test.c
SRCTESTPATH = libqueue.c 

all :
	$(CC) $(CFLAGS) -c $(MAIN) $(LIBS)
	ar rcs libqueue.a libqueue.o
	$(CC) $(MAIN) $(CFLAGS) -g -L. -lqueue -o main 

debug :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS)
	valgrind ./a.out

.PHONY: test
test: 
	$(CC) $(CFLAGS) $(TESTINPATH) $(UNITYPATH) $(SRCTESTPATH) $(TESTPATH) -o queuetest