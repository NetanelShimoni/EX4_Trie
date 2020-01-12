CC=gcc
FLAGS= -Wall -c

all: frequency

frequency: main.o
	$(CC) -Wall -o frequency main.o
main.o: main.c
	$(CC) -Wall -c main.c

.PHONY: clean all

clean:
	rm -f *.o *.a frequency a.out