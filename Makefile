CC=gcc
CFLAGS=-O2 -ggdb -Wall -Iinclude
LIBS=-Llib -lcs -lm

all: connect4

connect4: connect4.o
	$(CC) -o connect4 connect4.o $(LIBS)

clean:
	rm -f connect4.o connect4

run: connect4
	./connect4
