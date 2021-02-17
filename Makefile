CC=gcc
CFLAGS=-Wall -Werror -std=c99
OUT=-o bankControl
all:
	$(CC) src/*.c $(CFLAGS) $(OUT);
