CC = gcc
MAIN = loop.c
CFLAGS = -Wall -Wextra -pthread -fsanitize=address
DEBUGFLAGS = -Wall -Wextra -g
DEBUGFLAGS_SANTIZE = -Wall -Wextra -g -fsanitize=address

all :
	$(CC) $(CFLAGS) -c mutx.c 
	ar r libmutx.a mutx.o
	$(CC) $(MAIN) $(CFLAGS) -g -L. -lmutx -o main 

debug :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS)
	valgrind ./a.out

debug2 :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS_SANTIZE)
	./a.out
