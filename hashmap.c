#include "hashmap.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* getHash: implementation of FNV-1 hash algorithm 64-bit */
uint64_t GetHash(const char * const key, const size_t length) {
	const uint64_t prime = 1099511628211;	// FNV_prime 64-bits
	uint64_t hash = 14695981039346656037ull; // FNV_offset 64-bits

	for (int i = 0; i < length; i++) {
		hash *= prime;
		hash ^= key[i];
	}
	return hash;
}

/* HashMapCreate: return a pointer to a new empty hashmap */
hashmap_t *HashMapCreate(size_t length) {
	hashmap_t *map = (hashmap_t *)malloc(sizeof(hashmap_t));
	if (map == NULL)
		return NULL;
	map->length = length;
	map->members = (hnode_t **)calloc(sizeof(hnode_t *), length);
	if (map->members == NULL) {
		free((void *)map);
		return NULL;
	}
	for (size_t i = 0; i < length; i++) {
		map->members[i] = NULL;
	}
	return map;
}

static inline hnode_t *CreateNode(const char *key, const void *data,
		const size_t n) {
	hnode_t *m = (hnode_t *)malloc(sizeof(hnode_t));
	if (m == NULL)
		return NULL;
	if ((m->key = strdup(key)) == NULL) {
		free((void *)m);
		return NULL;
	}
	if ((m->data = malloc(n)) == NULL) {
		free((void *)m->key);
		free((void *)m);
		return NULL;
	}
	memcpy(m->data, data, n);
	return m;
}

static inline bool UpdateNode(hnode_t *m, const void *data, const size_t n) {
	free(m->data);
	if ((m->data = malloc(n)) == NULL)
		return false;
	memcpy(m->data, data, n);
	return true;
}

/* HashMapAdd: add a key value pair to a hashmap and return pointer to node */
void *HashMapAdd(hashmap_t *map, const char *key, const void *data,
		const size_t n) {
	uint64_t hash = GetHash(key, strlen(key)) % map->length;
	hnode_t *member = map->members[hash];
	for (size_t j = 0, i = hash; j < map->length; j++, i = (hash + (j * j)) %
			map->length) {
		member = map->members[i];
		if (member == NULL) {
			map->members[i] = CreateNode(key, data, n);
			return member;
		} else if (strcmp(member->key, key) == 0) {
			if (!UpdateNode(member, data, n))
				return NULL;
			return member;
		}
	}
	return NULL;
}

/* HashMapGet: return a pointer to the value for a key or NULL if it doesn't
 * exist */
void *HashMapGet(hashmap_t *map, char *key) {
	uint64_t hash = GetHash(key, strlen(key)) % map->length;
	for (size_t j = 0, i = hash; j < map->length; j++, i = (hash + (j * j)) %
			map->length) {
		hnode_t *member = map->members[i];
		if (member != NULL && strcmp(member->key, key) == 0) {
			return member->data;
		}
	}
	return NULL;
}

/* HashMapDeleteKey: delete a member from the table based on the key, return 0
 * if found and deleted otherwise return -1 */
int HashMapDeleteKey(hashmap_t *map, char *key) {
	uint64_t hash = GetHash(key, strlen(key)) % map->length;
	for (size_t j = 0, i = hash; j < map->length; j++, i = (hash + (j * j)) %
			map->length) {
		hnode_t *member = map->members[i];
		if (strcmp(member->key, key) == 0) {
			free((void *)member->data);
			free((void *)member);
			map->members[i] = NULL;
			return 0;
		}
	}
	return -1;
}

/* HashMapDelete: Free all of the members of the hashmap and then the hashmap */
void HashMapDelete(hashmap_t *map) {
	for (size_t i = 0; i < map->length; i++) {
		hnode_t *member = map->members[i];
		if (member == NULL)
			continue;
		free((void *)member->key);
		free((void *)member->data);
		free((void *)member);
	}
	free((void *)map->members);
	free((void *)map);
}

