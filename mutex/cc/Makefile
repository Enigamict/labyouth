CC = g++
MAIN = test.cc
TARGET = main
CFLAGS = -Wall -Wextra -pthread
DEBUGFLAGS = -Wall -Wextra -g
DEBUGFLAGS_SANTIZE = -Wall -Wextra -g -fsanitize=address

all :
	$(CC) $(MAIN) $(CFLAGS) -o $(TARGET)

asm :
	$(CC) -fno-asynchronous-unwind-tables $(MAIN) $(CFLAGS) -S
