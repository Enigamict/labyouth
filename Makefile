CC = gcc
MAIN = main.c 
LIBS = stack/libstack.c 
CFLAGS = -Wall -Wextra -O2

all: $(MAIN) $(LIBS)
	$(CC) $(CFLAGS) -c $(MAIN) $(LIBS)
	ar rcs libstack.a stack/libstack.o
	$(CC) $(MAIN) $(CFLAGS) -o main -L. -lstack
