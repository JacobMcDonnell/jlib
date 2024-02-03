#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

jhinit(fib, long, uint64_t, 1000);

long fib(long, jhfib_t *);

int main(int argc, char **argv)
{
	int n = atoi(argv[1]);

	jhfib_t *map;

	map = jhfib_createMap();

	printf("%ld\n", fib(n, map));

}

long fib(long n, jhfib_t *cache)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	long f = 0;
	if ((f = jhfib_get(cache, n)) == EOF) {
		f = fib(n-1, cache) + fib(n-2, cache);
		jhfib_add(cache, n, f);
	}
	return f;
}

