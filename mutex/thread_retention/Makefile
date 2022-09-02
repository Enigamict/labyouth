CC = gcc
MAIN = main.c
TARGET = main
CFLAGS = -Wall -Wextra -pthread -fsanitize=address
DEBUGFLAGS = -Wall -Wextra -g
DEBUGFLAGS_SANTIZE = -Wall -Wextra -g -fsanitize=address
OBJ=$(SRC:.c=.o)

all :
	$(CC) $(MAIN) $(CFLAGS) -o $(TARGET)

debug :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS)
	valgrind ./a.out

debug2 :
	$(CC) $(MAIN) $(LIBS) $(DEBUGFLAGS_SANTIZE)
	./a.out

clean:
	$(RM) -rf $(OBJ) $(TARGET)

.PHONY: clean
