CC = clang
CFLAGS = -Wall # Flag to pass to clang

fib: fib.c
	$(CC) $(CFLAGS) -c fib.c
	clang $(CFLAGS) -o fib fib.o hashmap.o

test: test.c
	$(CC) $(CFLAGS) -c test.c
	$(CC) $(CFLAGS) -o test test.o hashmap.o

clean:
	rm fib.o test.o fib test
