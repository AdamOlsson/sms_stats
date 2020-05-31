
CC=gcc
CFLAGS=-I.
DEPS = util.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main2: main.o util.o
	$(CC) -o main util.o main.o | ./main

main: main.c util.c util.h sort.c sort.h
	gcc -o main util.c main.c sort.c