SHELL=/bin/bash
CFLAGS= -std=c99 -Wall -pedantic -g -DDEBUG
CC=gcc

.PHONY: clean

all: Agent

heuristic.o: heuristic.h heuristic.c
search.o: search.c search.h
board.o: board.c board.h

Agent: main.c heuristic.o board.o search.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o Agent
