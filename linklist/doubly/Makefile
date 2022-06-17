CC = gcc
MAIN = main.c
LIBS = liblinklist.c
CFLAGS = -Wall -Wextra -O2
DEBUGFLAGS = -Wall -Wextra -g
DEBUGFLAGS_SANTIZE = -Wall -Wextra -g -fsanitize=address


all :
	$(CC) $(CFLAGS) -c $(MAIN) $(LIBS)
	ar rcs liblinklist.a liblinklist.o
	$(CC) $(MAIN) $(CFLAGS) -g -L. -llinklist -o main 

debug :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS)
	valgrind ./a.out

debug2 :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS)
	./a.out
