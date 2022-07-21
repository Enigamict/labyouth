CC = gcc
MAIN = stack.c
LIBS = ../doubly
CFLAGS = -Wall -Wextra -O2
DEBUGFLAGS = -Wall -Wextra -g
DEBUGFLAGS_SANTIZE = -Wall -Wextra -g -fsanitize=address


all :
	$(CC) $(CFLAGS) -I $(LIBS) -c $(MAIN) ../doubly/liblinklist.c
	ar rcs liblinklist.a liblinklist.o
	$(CC) $(MAIN) $(CFLAGS) -g -L. -llinklist -o main -I $(LIBS) 

debug :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS)
	valgrind ./a.out

debug2 :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS)
	./a.out
