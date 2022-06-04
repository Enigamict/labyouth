CC = gcc
MAIN = main.c 
LIBS = libstack.c
CFLAGS = -Wall -Wextra -O2

TESTINPATH = -I ./ -I ../../lib/Unity/src -I ../../lib/Unity/extras/fixture/src/ -I ../../lib/Unity/extras/memory/src
UNITYPATH = ../../lib/Unity/src/unity.c ../../lib/Unity/extras/fixture/src/unity_fixture.c ../../lib/Unity/extras/memory/src/unity_memory.c
TESTPATH = ../../test/testcase/test_stack_init.c ../../test/testcase/test_stack_push.c ../../test/testcase/test_stack_pop.c ../../test/testrun/test_run.c ../../test/testrun/all_test.c
SRCTESTPATH = libstack.c 

all :
	$(CC) $(CFLAGS) -c $(MAIN) $(LIBS)
	ar rcs libstack.a libstack.o
	$(CC) $(MAIN) $(CFLAGS) -g -L. -lstack -o main 

.PHONY: test
test: 
	$(CC) $(CFLAGS) $(TESTINPATH) $(UNITYPATH) $(SRCTESTPATH) $(TESTPATH) -o stacktest