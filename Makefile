CC=gcc 
CFLAGS=-Wall -g

all: v1
v1: v1.o
v1.o: v1.c

clean:
	rm -f v1.exe v1.o
run: v1
	./v1
