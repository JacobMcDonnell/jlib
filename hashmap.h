#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define jhinit(name, keyType, dataType, size) \
	typedef struct _node##name##_t { \
		keyType data; \
		dataType key; \
		struct _node##name##_t *next; \
	} _node##name##_t; \
	const size_t jh##name##_size = size; \
	struct hashmap##name##_t { \
		struct _node##name##_t *members[size]; \
	}; \
	typedef struct hashmap##name##_t jh##name##_t; \
	_jhimple(name, keyType, dataType, size);


#define _jproto(name, keyType, dataType, size) \
	struct _node##name##_t *jh##name##_add(struct hashmap##name##_t *map, keyType key, dataType data); \
	dataType jh##name##_get(struct hashmap##name##_t *map, keyType key); \
	int jh##name##_deleteKey(struct hashmap##name##_t *map, keyType key); \
	struct hashmap##name##_t *jh##name##_createMap(void); \


#define _jhimple(name, keyType, dataType, size) \
	_jproto(name, keyType, dataType, size); \
	/* createMap: return a pointer to a new empty hashmap */ \
	struct hashmap##name##_t *jh##name##_createMap(void) \
	{ \
		return (struct hashmap##name##_t *)malloc(sizeof(struct hashmap##name##_t)); \
	} \
	/* jh##name##_addNode: return a pointer to a new node after the given node */ \
	static struct _node##name##_t *jh##name##_createNode(keyType key, dataType data) \
	{ \
		struct _node##name##_t *new = (struct _node##name##_t *)malloc(sizeof(struct _node##name##_t)); \
		if (new == NULL) \
			return NULL; \
		new->key = key; \
		new->data = data; \
		new->next = NULL; \
		return new; \
	} \
	/* add: add a key value pair to a hashmap and return pointer to node */ \
	struct _node##name##_t *jh##name##_add(struct hashmap##name##_t *map, keyType key, dataType data) \
	{ \
		int hash = getHashInt(key) % size; \
		struct _node##name##_t *np = map->members[hash]; \
		if (np == NULL) { \
			np = jh##name##_createNode(key, data); \
			map->members[hash] = np; \
			return np; \
		} else if (np->key == key) { \
			np->data = data; \
			return np; \
		} \
		while (np->next != NULL) { \
			if (np->key == key) { \
				np->data = data; \
				return np; \
			} \
			np = np->next; \
		} \
		np->next = jh##name##_createNode(key, data); \
		return np; \
	} \
	/* get: return the value for a key or EOF if it doesn't exist */ \
	dataType jh##name##_get(struct hashmap##name##_t *map, keyType key) \
	{ \
		int hash = getHashInt(key) % size; \
		struct _node##name##_t *np = map->members[hash]; \
		while (np != NULL) { \
			if (np->key == key) \
				return np->data; \
			np = np->next; \
		} \
		return EOF; \
	} \
	/* deleteKey: delete a member from the table based on the key */ \
	int jh##name##_deleteKey(struct hashmap##name##_t *map, keyType key) \
	{ \
		int hash = getHashInt(key) % size; \
		struct _node##name##_t *np = map->members[hash], *prev = NULL; \
		if (np->key == key) { \
			map->members[hash] = map->members[hash]->next; \
			free((void *)np); \
			return 0; \
		} \
		while (np != NULL) { \
			if (np->key == key) { \
				prev->next = np->next; \
				free((void *)np); \
				return 0; \
			} \
			prev = np; \
			np = np->next; \
		} \
		return -1; \
	}

uint64_t getHash(const uint8_t *key, size_t length);
uint64_t getHashInt(uint8_t key);

