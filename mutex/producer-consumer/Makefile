CC = gcc
MAIN = main.c
CFLAGS = -Wall -Wextra -pthread 
DEBUGFLAGS = -Wall -Wextra -g
DEBUGFLAGS_SANTIZE = -Wall -Wextra -g -fsanitize=address
LIBS = ../linklist/doubly ../linklist/queue
OBJ=$(MAIN:.c=.o)

all :
	$(CC) $(CFLAGS) -I ../../linklist/queue -I ../../linklist/doubly -c $(MAIN) ../../linklist/queue/queue.c ../../linklist/doubly/liblinklist.c
	ar rcs libqueue.a queue.o liblinklist.o
	$(CC) $(MAIN) $(CFLAGS) -g -L. -lqueue -o main

.PHONY: clean
clean:
	$(RM) -rf $(OBJ) $(TARGET)
