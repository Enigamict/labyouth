CC = gcc
CCC = g++
MAIN = main.c 
CCMAIN = main.cc
LIBS = tree/libtree.c
LIBS_OBJ = libtree.a \
           libtree.o
CFLAGS = -Wall -Wextra 
MAIN_OBJ =$(MAIN:.c=.o)


TESTINPATH = -I ./ -I lib/Unity/src -I lib/Unity/extras/fixture/src/ -I lib/Unity/extras/memory/src
UNITYPATH = lib/Unity/src/unity.c lib/Unity/extras/fixture/src/unity_fixture.c lib/Unity/extras/memory/src/unity_memory.c
TESTPATH = test/testcase/test_stack_init.c test/testcase/test_stack_push.c test/testcase/test_stack_pop.c test/testrun/test_run.c test/testrun/all_test.c
SRCTESTPATH = stack/libstack.c 

tree: main.o
	$(CC) $(MAIN)  $(CFLAGS) -o main -g -L. -ltree

main.o : main.c
	$(CC) $(CFLAGS) -c $(MAIN) $(LIBS)
	ar rcs libtree.a libtree.o

queue:
	$(CC) $(CFLAGS) -c $(MAIN) $(LIBS)
	ar rcs libqueue.a libqueue.o
	$(CC) $(MAIN)  $(CFLAGS) -o main -L. -lqueue

.PHONY: test
test: 
	$(CC) $(CFLAGS) $(TESTINPATH) $(UNITYPATH) $(SRCTESTPATH) $(TESTPATH) -o stacktest

.PHONY: clean
clean:
	rm -f $(LIBS_OBJ) $(MAIN_OBJ)