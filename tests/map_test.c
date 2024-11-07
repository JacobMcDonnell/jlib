#include "../hashmap.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void MapTest(void) {
	printf("Creating Map: ");
	const size_t n = 100;
	hashmap_t *map = HashMapCreate(n);
	assert(map != NULL);
	assert(map->members != NULL);
	assert(map->length == n);
	printf("Passed.\nSet \"tips\" to 10: ");

	int t = 10, x;
	HashMapAdd(map, "tips", &t, sizeof(int));
	void *v = HashMapGet(map, "tips");
	assert(v != NULL);
	x = *(int *)v;
	assert(t == x);
	printf("Passed.\nUpdate \"tips\" to 20: ");

	t = 20;
	x = 0;
	HashMapAdd(map, "tips", &t, sizeof(int));
	v = HashMapGet(map, "tips");
	assert(v != NULL);
	x = *(int *)v;
	assert(t == x);
	printf("Passed.\nDelete Key \"tips\": ");

	HashMapDeleteKey(map, "tips");
	assert(HashMapGet(map, "tips") == NULL);
	printf("Passed.\nDelete Map: ");

	HashMapDelete(map);
	map = NULL;
	printf("Passed.\nTest Conflict: ");

	map = HashMapCreate(2);
	assert(map != NULL);
	assert(map->members != NULL);
	assert(map->length == 2);

	t = 10;
	HashMapAdd(map, "tips", &t, sizeof(t));
	int g = 20;
	HashMapAdd(map, "pits", &g, sizeof(g));

	v = HashMapGet(map, "tips");
	assert(v != NULL);
	x = *(int *)v;
	assert(x == t);

	v = HashMapGet(map, "pits");
	assert(v != NULL);
	x = *(int *)v;
	assert(x == g);
	HashMapDelete(map);

	printf("Passed.\n");
}

