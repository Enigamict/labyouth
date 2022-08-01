CC = gcc
MAIN = main.c
LIBS = ../doubly
CFLAGS = -Wall -Wextra 
DEBUGFLAGS = -Wall -Wextra -g
DEBUGFLAGS_SANTIZE = -Wall -Wextra -g -fsanitize=address


all :
	$(CC) $(CFLAGS) -I $(LIBS) -I./ -c $(MAIN) ../doubly/liblinklist.c queue.c
	ar rcs liblinklist.a liblinklist.o queue.o
	$(CC) $(MAIN) $(CFLAGS) -g -L. -llinklist -o main -I $(LIBS) -I ./

debug :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS)
	valgrind ./a.out

debug2 :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS)
	./a.out
