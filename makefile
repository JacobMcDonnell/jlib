CC = clang
CFLAGS = -Wall # Flag to pass to clang

hashmap.o: hashmap.c
	$(CC) $(CFLAGS) -c hashmap.c

clean:
	rm hashmap.o
