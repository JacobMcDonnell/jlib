#include "hashmap.h"
#include <stdio.h>

jhinit(32, int, long, 1000);

int main()
{
	jh32_t *map = jh32_createMap();
	_node32_t *np;

	jh32_add(map, 4, 8);
	printf("%d: %ld\n", 4, jh32_get(map, 4));

	jh32_add(map, 4, 12);
	printf("%d: %ld\n", 4, jh32_get(map, 4));

	for (int i = 4; i < 10 * jh32_size + 1; i += jh32_size) {
		np = jh32_add(map, i, i*2);
		if (np == NULL)
			printf("ERROR\n");
	}

	for (int i = 4; i < 10 * jh32_size + 1; i += jh32_size) {
		int d = jh32_get(map, i);
		printf("%4d: %4d\t%4llu\n", i, d, getHashInt(i) % jh32_size);
	}

	int j;
	j = jh32_deleteKey(map, 4);
	printf("delete of %d code = %d\n", 4, j);

	j = jh32_deleteKey(map, 8004);

	printf("delete of %d code = %d\n", 8004, j);

	for (int i = 4; i < 10 * jh32_size + 1; i += jh32_size) {
		int d = jh32_get(map, i);
		printf("%4d: %4d\t%4llu\n", i, d, getHashInt(i) % jh32_size);
	}

	return 0;
}
