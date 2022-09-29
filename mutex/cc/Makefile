CC = g++
MAIN = atomic.cc
TARGET = main
CFLAGS = -Wall -Wextra -pthread
DEBUGFLAGS = -Wall -Wextra -g
DEBUGFLAGS_SANTIZE = -Wall -Wextra -g -fsanitize=address

all :
	$(CC) $(MAIN) $(CFLAGS) -o $(TARGET)