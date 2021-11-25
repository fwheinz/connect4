CC=gcc
CFLAGS=-O2 -ggdb -Wall -Iinclude
LIBS=-Llib -lcs -lm
SHELL=/bin/bash

all: connect4

connect4: connect4.o
	$(CC) -o connect4 connect4.o $(LIBS)

clean:
	rm -f connect4.o connect4

run: connect4
	./connect4

submit:
	@read -p "Your name: " NAME; echo Submitting for $$NAME; curl -F "connect4=@connect4.c;filename=connect4_$${NAME//\ /_}.c" http://pg1.sysv.de/submit.php; echo Done.
