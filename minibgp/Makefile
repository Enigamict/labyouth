CC = gcc
MAIN = bgpd
LIBS = libbuf.c
CFLAGS = -Wall -Wextra
DEBUGFLAGS = -Wall -Wextra -g
DEBUGFLAGS_SANTIZE = -Wall -Wextra -g

all :
	$(CC) $(CFLAGS) -c libbuf.c rib.c bgpd.c
	ar rcs libbuf.a libbuf.o rib.o
	$(CC) bgpd.c $(CFLAGS) -g -L. -lbuf -o $(MAIN)

.PHONY: clean
clean:
	rm main