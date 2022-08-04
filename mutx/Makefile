CC = gcc
MAIN = main
LIBS = ../doubly
CFLAGS = -Wall -Wextra 
DEBUGFLAGS = -Wall -Wextra -g
DEBUGFLAGS_SANTIZE = -Wall -Wextra -g -fsanitize=address


all :
	$(CC) $(CFLAGS) -o client client.c
	$(CC) $(CFLAGS) -o server server.c

debug :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS)
	valgrind ./a.out

debug2 :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS)
	./a.out
