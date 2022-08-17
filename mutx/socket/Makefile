CC = gcc
MAIN = main
CFLAGS = -Wall -Wextra -pthread -fsanitize=address
DEBUGFLAGS = -Wall -Wextra -g
DEBUGFLAGS_SANTIZE = -Wall -Wextra -g -fsanitize=address


all :
	$(CC) $(CFLAGS) -o client client.c
	$(CC) $(CFLAGS) -o server server.c
