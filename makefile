CC = gcc
CFLAGS = -Wall -Werror -std=c99 -g
OBJ = list.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)

tests: $(OBJ)
	$(CC) -g -o tests/tester tests/tester.c $^ $(CFLAGS)

clean:
	rm -f *.o tests/*.o