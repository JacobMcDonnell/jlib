CC = gcc
CFLAGS = -Wall -Werror -std=c99 -g
OBJ = list.o hashmap.o

%.o: %.c %.h
	$(CC) -c $< $(CFLAGS)

all: $(OBJ)

tests: tests/tester.o $(OBJ)
	$(CC) -o tests/tester $^ $(CFLAGS)

clean:
	rm -f *.o tests/*.o tests/tester
