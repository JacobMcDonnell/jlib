#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>
#include <stddef.h>

typedef struct hnode_t {
	void *data;
	char *key;
} hnode_t;

typedef struct hashmap_t {
	size_t length;
	size_t full;
	hnode_t **members;
} hashmap_t;

uint64_t GetHash(const char * const key, const size_t length);
hashmap_t *HashMapCreate(size_t length);
void *HashMapAdd(hashmap_t *map, const char *key, const void *data,
		const size_t n);
void *HashMapGet(hashmap_t *map, char *key);
int HashMapDeleteKey(hashmap_t *map, char *key);
void HashMapDelete(hashmap_t *map);

#endif
