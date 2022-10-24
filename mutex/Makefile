CC = gcc
MAIN = loop.c
TARGET = main
CFLAGS = -Wall -Wextra -pthread -fsanitize=address
DEBUGFLAGS = -Wall -Wextra -g
DEBUGFLAGS_SANTIZE = -Wall -Wextra -g -fsanitize=address
OBJ=$(MAIN:.c=.o)

all :
	$(CC) $(CFLAGS) -c mutx.c 
	ar r libmutx.a mutx.o
	$(CC) $(MAIN) $(CFLAGS) -g -L. -lmutx -o $(TARGET)

debug :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS)
	valgrind ./a.out

debug2 :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS_SANTIZE)
	./a.out

clean:
	$(RM) -rf $(OBJ) $(TARGET)

.PHONY: clean
