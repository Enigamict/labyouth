CC = gcc
MAIN = main.c
LIBS = liblinklist.c
CFLAGS = -Wall -Wextra -O2
DEBUGFLAGS = -Wall -Wextra -g


all :
	$(CC) $(CFLAGS) -c $(MAIN) $(LIBS)
	ar rcs liblinklist.a liblinklist.o
	$(CC) $(MAIN) $(CFLAGS) -g -L. -llinklist -o main 

debug :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS)
	valgrind ./a.out
