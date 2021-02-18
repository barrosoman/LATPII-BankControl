CC=gcc
CFLAGS=-Wall -Werror -std=c99
OUT=-o libraryControl
all:
	$(CC) src/*.c $(CFLAGS) $(OUT);
